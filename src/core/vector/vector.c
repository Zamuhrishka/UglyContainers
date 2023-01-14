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
//_____ D E F I N I T I O N S _________________________________________________
struct Private_tag
{
    void* this;
    void* pool;
    size_t esize;
    size_t size;
    size_t capacity;
};

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________
static bool push_front_cb(void* vector, const void* data)
{
    assert(vector);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    vector_t* vec = (vector_t*)vector;

    return false;
}

static bool pop_front_cb(void* vector, void* data)
{
    assert(vector);
    assert(data);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    vector_t* vec = (vector_t*)vector;

    return false;
}

static bool push_back_cb(void* vector, const void* data)
{
    assert(vector);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    vector_t* vec = (vector_t*)vector;

    return false;
}

static bool pop_back_cb(void* vector, void* data)
{
    assert(vector);
    assert(data);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    vector_t* vec = (vector_t*)vector;

    return false;
}

static bool insert_cb(void* vector, const void* data, size_t position)
{
    assert(vector);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    vector_t* vec = (vector_t*)vector;

    return false;
}

static bool at_cb(const void* vector, void* data, size_t position)
{
    assert(vector);
    assert(data);

    vector_t* vec = (vector_t*)vector;

    return false;
}

static bool erase_cb(void* vector, size_t position)
{
    assert(vector);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    vector_t* vec = (vector_t*)vector;

    return false;
}

static size_t size_cb(const void* vector)
{
    assert(vector);

    vector_t* vec = (vector_t*)vector;

    return vec->private->size;
}

//_____ P U B L I C  F U N C T I O N S_________________________________________
vector_t* vector_create(size_t esize)
{
    assert(0 != esize);

    if (!is_allocator_valid())
    {
        return false;
    }

    allocate_fn_t mem_allocate = get_allocator();
    free_fn_t mem_free = get_free();

    vector_t* vector = (vector_t*)mem_allocate(sizeof(*vector));
    if (vector == NULL)
    {
        return NULL;
    }

    private_t* member = (private_t*)mem_allocate(sizeof(private_t));
    if (NULL == member)
    {
        mem_free(vector);
        return NULL;
    }

    void* pool = (void*)mem_allocate(DEFAULT_CAPACITY * esize);
    if (pool == NULL)
    {
        mem_free(member);
        mem_free(vector);
        return NULL;
    }

    vector->private = member;
    vector->private->this = vector;
    vector->private->size = 0;
    vector->private->capacity = DEFAULT_CAPACITY;
    vector->private->esize = esize;
    vector->private->pool = pool;

    vector->push_front = push_front_cb;
    vector->pop_front = pop_front_cb;
    vector->push_back = push_back_cb;
    vector->pop_back = pop_back_cb;
    vector->insert = insert_cb;
    vector->at = at_cb;
    vector->erase = erase_cb;
    vector->size = size_cb;

    return vector;
}

bool vector_delete(vector_t** vector)
{
    return false;
}
