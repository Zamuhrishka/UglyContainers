/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "vector.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
#define DEFAULT_CAPACITY 10
#define RESIZE_FACTOR DEFAULT_CAPACITY
//_____ D E F I N I T I O N S _________________________________________________
struct Private_tag
{
  void* pool;               /// Pool of bytes
  size_t esize;             /// Single element size
  volatile size_t size;     /// Stores elements number
  volatile size_t capacity; /// Max size of pool in bytes
};

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________
static inline vector_t* vector_allocate(void)
{
  if (!is_allocator_valid())
  {
    return NULL;
  }

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  // TODO: Add some align checking?
  // NOTE: Apply **SIZEOF TO VARIABLES** idiom
  vector_t* vector = (vector_t*)mem_allocate(sizeof *vector);
  if (NULL == vector)
  {
    return NULL;
  }

  // TODO: Apply **SIZEOF TO VARIABLES** idiom
  vector->private = (private_t*)mem_allocate(sizeof(private_t));
  if (NULL == vector->private)
  {
    mem_free(vector);
    return NULL;
  }

  vector->private->capacity = 0;
  vector->private->esize = 0;
  vector->private->size = 0;
  vector->private->pool = NULL;

  return vector;
}

static inline bool vector_reallocate(vector_t* vector, size_t new_size)
{
  size_t new_size_in_bytes = (vector->private->size * vector->private->esize) + (new_size * vector->private->esize);

  allocate_fn_t mem_allocate = get_allocator();
  assert(mem_allocate);
  free_fn_t mem_free = get_free();
  assert(mem_free);

  void* data = mem_allocate(new_size_in_bytes);
  if (NULL == data)
  {
    return NULL;
  }

  size_t size_in_bytes = vector->private->size * vector->private->esize;
  memcpy(data, vector->private->pool, size_in_bytes);

  mem_free(vector->private->pool);

  vector->private->pool = data;
  vector->private->capacity = new_size_in_bytes;

  return true;
}

#if 0
static inline bool vector_decrease(vector_t *vector)
{
    size_t current_size_in_bytes = vector->private->size * vector->private->esize;
    size_t resize_factor_size_in_bytes = RESIZE_FACTOR * vector->private->esize;

    if(current_size_in_bytes < resize_factor_size_in_bytes)
    {
        return false;
    }

	size_t new_size_in_bytes = current_size_in_bytes - resize_factor_size_in_bytes;

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);
    free_fn_t mem_free = get_free();
    assert(mem_free);

    void* data = mem_allocate(new_size_in_bytes);
    if (NULL == data)
    {
        return NULL;
    }

    size_t size_in_bytes = vector->private->size * vector->private->esize;
    memcpy(data, vector->private->pool, size_in_bytes);

	mem_free(vector->private->pool);

	vector->private->pool = data;
	vector->private->capacity = new_size_in_bytes;

	return true;
}
#endif

static inline void vector_free(vector_t* vector)
{
  assert(vector);

  free_fn_t mem_free = get_free();
  assert(mem_free);

  mem_free(vector->private->pool);
  mem_free(vector->private);
  mem_free(vector);
}

static inline void* pool_allocate(size_t size_in_bytes)
{
  allocate_fn_t mem_allocate = get_allocator();
  assert(mem_allocate);

  void* pool = mem_allocate(size_in_bytes);
  if (NULL == pool)
  {
    return NULL;
  }

  memset(pool, 0, size_in_bytes);

  return pool;
}

static bool is_empty(const vector_t* vector)
{
  // assert(vector);
  return (vector->private->size == 0);
}

static bool is_full(const vector_t* vector)
{
  // assert(vector);
  return (vector->private->size == vector->private->capacity);
}

static size_t free_space(const vector_t* vector)
{
  // assert(vector);
  return (vector->private->capacity - (vector->private->size * vector->private->esize));
}

static bool is_free_space_for_element(const vector_t* vector)
{
  // assert(vector);
  size_t free_space_in_bytes = free_space(vector);
  return (free_space_in_bytes >= vector->private->esize);
}

static bool resize_cb(void* vector, size_t new_size)
{
  assert(vector);

  vector_t* _vector = (vector_t*)vector;

  if (_vector->private->size >= new_size)
  {
    return true;
  }

  return vector_reallocate(_vector, new_size);
}

static bool push_front_cb(void* vector, const void* data)
{
  assert(vector);
  assert(data);

  allocate_fn_t mem_allocate = get_allocator();
  assert(mem_allocate);

  vector_t* _vector = (vector_t*)vector;

  if (!is_free_space_for_element(_vector))
  {
    if (!vector_reallocate(_vector, RESIZE_FACTOR))
    {
      return false;
    }
  }

  size_t size_in_bytes = _vector->private->size * _vector->private->esize;
  uint8_t* dst = &_vector->private->pool[size_in_bytes + _vector->private->esize];
  uint8_t* src = &_vector->private->pool[size_in_bytes];
  for (size_t i = 0; i < size_in_bytes; i++)
  {
    *(--dst) = *(--src);
  }

  memcpy(&_vector->private->pool[0], data, _vector->private->esize);

  _vector->private->size++;

  return true;
}

static bool pop_front_cb(void* vector, void* data)
{
  assert(vector);
  assert(data);

  vector_t* _vector = (vector_t*)vector;

  if (is_empty(_vector))
  {
    return false;
  }

  memcpy(data, &_vector->private->pool[0], _vector->private->esize);

  size_t size_in_bytes = _vector->private->size * _vector->private->esize;
  uint8_t* dst = &_vector->private->pool[0];
  uint8_t* src = &_vector->private->pool[_vector->private->esize];
  for (size_t i = 0; i < size_in_bytes; i++)
  {
    dst[i] = src[i];
  }

  _vector->private->size--;

  return true;
}

static bool push_back_cb(void* vector, const void* data)
{
  assert(vector);
  assert(data);

  vector_t* _vector = (vector_t*)vector;

  if (!is_free_space_for_element(_vector))
  {
    if (!vector_reallocate(_vector, RESIZE_FACTOR))
    {
      return false;
    }
  }

  size_t size_in_bytes = _vector->private->size * _vector->private->esize;
  memcpy(&_vector->private->pool[size_in_bytes], data, _vector->private->esize);

  _vector->private->size++;

  return true;
}

static bool pop_back_cb(void* vector, void* data)
{
  assert(vector);
  assert(data);

  vector_t* _vector = (vector_t*)vector;

  if (is_empty(_vector))
  {
    return false;
  }

  size_t size_in_bytes = _vector->private->size * _vector->private->esize;
  size_t offset_in_bytes = size_in_bytes - _vector->private->esize;
  memcpy(data, &_vector->private->pool[offset_in_bytes], _vector->private->esize);

  _vector->private->size--;

  return true;
}

static bool insert_cb(void* vector, const void* data, size_t index)
{
  assert(vector);
  assert(data);

  vector_t* _vector = (vector_t*)vector;

  if (index > _vector->private->size)
  {
    return false;
  }

  if (!is_free_space_for_element(_vector))
  {
    if (!vector_reallocate(_vector, RESIZE_FACTOR))
    {
      return false;
    }
  }

  size_t offset_in_bytes = index * _vector->private->esize;
  size_t size_in_bytes = _vector->private->size * _vector->private->esize;
  size_t byte_number = size_in_bytes - offset_in_bytes;
  uint8_t* dst = &_vector->private->pool[size_in_bytes + _vector->private->esize];
  uint8_t* src = &_vector->private->pool[size_in_bytes];
  for (size_t i = 0; i < byte_number; i++)
  {
    *(--dst) = *(--src);
  }

  memcpy(&_vector->private->pool[offset_in_bytes], data, _vector->private->esize);

  _vector->private->size++;

  return true;
}

static bool extract_cb(void* vector, void* data, size_t index)
{
  assert(vector);
  assert(data);

  vector_t* _vector = (vector_t*)vector;

  if (index > _vector->private->size || is_empty(_vector))
  {
    return false;
  }

  if (!_vector->at(_vector, data, index))
  {
    return false;
  }

  if (!_vector->erase(_vector, index))
  {
    return false;
  }

  return true;
}

static bool replace_cb(void* vector, const void* data, size_t index)
{
  assert(vector);
  assert(data);

  vector_t* _vector = (vector_t*)vector;

  if (index > _vector->private->size || is_empty(_vector))
  {
    return false;
  }

  size_t offset_in_bytes = index * _vector->private->esize;
  memcpy(&_vector->private->pool[offset_in_bytes], data, _vector->private->esize);

  return true;
}

static bool at_cb(const void* vector, void* data, size_t index)
{
  assert(vector);
  assert(data);

  vector_t* _vector = (vector_t*)vector;

  if (index > (_vector->private->size - 1) || is_empty(_vector))
  {
    return false;
  }

  size_t offset_in_bytes = index * _vector->private->esize;
  memcpy(data, &_vector->private->pool[offset_in_bytes], _vector->private->esize);

  return true;
}

static bool erase_cb(void* vector, size_t index)
{
  assert(vector);

  vector_t* _vector = (vector_t*)vector;

  if (index > (_vector->private->size - 1) || is_empty(_vector))
  {
    return false;
  }

  size_t offset_in_bytes = index * _vector->private->esize;
  size_t size_in_bytes = _vector->private->size * _vector->private->esize;
  size_t byte_number = size_in_bytes - offset_in_bytes;
  uint8_t* dst = &_vector->private->pool[offset_in_bytes];
  uint8_t* src = &_vector->private->pool[offset_in_bytes + _vector->private->esize];
  for (size_t i = 0; i < byte_number; i++)
  {
    dst[i] = src[i];
  }

  _vector->private->size--;

  return true;
}

static void* peek_cb(void* vector, size_t index)
{
  assert(vector);

  vector_t* _vector = (vector_t*)vector;

  if (index > (_vector->private->size - 1) || is_empty(_vector))
  {
    return false;
  }

  size_t offset_in_bytes = index * _vector->private->esize;
  return &_vector->private->pool[offset_in_bytes];
}

static bool clear_cb(void* vector)
{
  assert(vector);

  vector_t* _vector = (vector_t*)vector;

  if (is_empty(_vector))
  {
    return true;
  }

  size_t size_in_bytes = _vector->private->size * _vector->private->esize;
  uint8_t* dst = (uint8_t*)_vector->private->pool;
  for (size_t i = 0; i < size_in_bytes; i--)
  {
    dst[i] = 0;
  }

  _vector->private->size = 0;

  return true;
}

static size_t size_cb(const void* vector)
{
  assert(vector);

  return ((vector_t*)vector)->private->size;
}

//_____ P U B L I C  F U N C T I O N S_________________________________________
vector_t* vector_create(size_t esize)
{
  assert(0 != esize);

  vector_t* vector = vector_allocate();
  if (NULL == vector)
  {
    return NULL;
  }

  vector->private->size = 0;
  vector->private->capacity = DEFAULT_CAPACITY * esize;
  vector->private->esize = esize;
  vector->private->pool = pool_allocate(vector->private->capacity);
  if (NULL == vector->private->pool)
  {
    vector_free(vector);
    return NULL;
  }

  vector->resize = resize_cb;
  vector->push_front = push_front_cb;
  vector->pop_front = pop_front_cb;
  vector->push_back = push_back_cb;
  vector->pop_back = pop_back_cb;
  vector->insert = insert_cb;
  vector->extract = extract_cb;
  vector->replace = replace_cb;
  vector->at = at_cb;
  vector->erase = erase_cb;
  vector->peek = peek_cb;
  vector->clear = clear_cb;
  vector->size = size_cb;

  return vector;
}

void vector_delete(vector_t** vector)
{
  assert(vector);
  assert(*vector);

  // BUG: Check why tests fault on this pool free
  // vector_free((*vector)->private->pool);
  vector_free(*vector);
  (*vector) = NULL;
}
