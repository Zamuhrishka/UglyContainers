/**
 * \file    container.c
 * \author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Universal data storage container.
 *
 * This file contains function prototypes for working with a universal container.
 * The container can be implemented based on a linked list or a vector.
 * The provided functions allow for basic operations on the container,
 * such as adding, removing, extracting, and replacing elements.
 *
 * For correct operation with the container, before using the container functions,
 * it's necessary to initialize memory allocation and deallocation functions using
 * the `container_alloc_init` function.
 *
 * \date  2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "container.h"

#include "common/uc_assert.h"

#include "linked_list/linked_list.h"
#include "vector/vector.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
struct Container_tag
{
  void *core;
  container_type_e type;
};
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes the container allocator with custom memory functions.
 *
 * Detailed description see in container.h
 */
void container_alloc_init(allocate_fn_t alloc_cb, free_fn_t free_cb)
{
  UC_ASSERT(alloc_cb);
  UC_ASSERT(free_cb);

  allocation_cb_register(alloc_cb);
  free_cb_register(free_cb);
}

/**
 * \brief Creates a new container of a specified type.
 *
 * Detailed description see in container.h
 */
container_t *container_create(size_t esize, container_type_e type)
{
  UC_ASSERT(0 != esize);

  if (!is_allocator_valid())
  {
    return NULL;
  }

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  container_t *container = (container_t *)mem_allocate(sizeof *container);
  if (container == NULL)
  {
    return NULL;
  }

  container->type = type;
  container->core =
    ((CONTAINER_LINKED_LIST_BASED == type) ? (void *)linked_list_create(esize)
                                           : ((CONTAINER_VECTOR_BASED == type) ? (void *)vector_create(esize) : NULL));

  if (container->core == NULL)
  {
    mem_free(container);
    return NULL;
  }

  return container;
}

#if 0
container_t* container_from_array(void *arr, size_t size, size_t esize)
{
    UC_ASSERT(0 != esize);
    UC_ASSERT(0 != size);
    UC_ASSERT(arr);

    container_t* container = container_create(esize);
    if(NULL == container)
    {
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        container_push_back(container, ((uint8_t*)arr + i*esize));
    }

    return container;
}
#endif

/**
 * \brief Frees up the memory associated with the container.
 *
 * Detailed description see in container.h
 */
void container_delete(container_t **container)
{
  UC_ASSERT(container);
  UC_ASSERT(*container);
  UC_ASSERT(is_allocator_valid());

  free_fn_t mem_free = get_free();

  if (CONTAINER_LINKED_LIST_BASED == (*container)->type)
  {
    linked_list_t *pointer = (linked_list_t *)((*container)->core);
    linked_list_delete(&pointer);
  }
  else if (CONTAINER_VECTOR_BASED == (*container)->type)
  {
    vector_t *pointer = (vector_t *)((*container)->core);
    vector_delete(&pointer);
  }

  mem_free(*container);
  (*container) = NULL;
}

/**
 * \brief Resizes the container to a new size.
 *
 * Detailed description see in container.h
 */
bool container_resize(container_t *container, size_t new_size)
{
  UC_ASSERT(container);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->resize(((linked_list_t *)container->core), new_size)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->resize(((vector_t *)container->core), new_size)
                 : false));
}

/**
 * \brief Pushes an element to the front of the container.
 *
 * Detailed description see in container.h
 */
bool container_push_front(container_t *container, const void *data)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->push_front(((linked_list_t *)container->core), data)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->push_front(((vector_t *)container->core), data)
                 : false));
}

/**
 * \brief Pops an element from the front of the container.
 *
 * Detailed description see in container.h
 */
bool container_pop_front(container_t *container, void *data)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->pop_front(((linked_list_t *)container->core), data)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->pop_front(((vector_t *)container->core), data)
                 : false));
}

/**
 * \brief Pushes an element to the back of the container.
 *
 * Detailed description see in container.h
 */
bool container_push_back(container_t *container, const void *data)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->push_back(((linked_list_t *)container->core), data)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->push_back(((vector_t *)container->core), data)
                 : false));
}

/**
 * \brief Pops an element from the back of the container.
 *
 * Detailed description see in container.h
 */
bool container_pop_back(container_t *container, void *data)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->pop_back(((linked_list_t *)container->core), data)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->pop_back(((vector_t *)container->core), data)
                 : false));
}

/**
 * \brief Inserts an element at a specified index in the container.
 *
 * Detailed description see in container.h
 */
bool container_insert(container_t *container, const void *data, size_t index)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->insert(((linked_list_t *)container->core), data, index)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->insert(((vector_t *)container->core), data, index)
                 : false));
}

/**
 * \brief Extracts an element from a specified index in the container.
 *
 * Detailed description see in container.h
 */
bool container_extract(container_t *container, void *data, size_t index)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->extract(((linked_list_t *)container->core), data, index)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->extract(((vector_t *)container->core), data, index)
                 : false));
}

/**
 * \brief Replaces an element at a specified index in the container.
 *
 * Detailed description see in container.h
 */
bool container_replace(container_t *container, const void *data, size_t index)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->replace(((linked_list_t *)container->core), data, index)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->replace(((vector_t *)container->core), data, index)
                 : false));
}

/**
 * \brief Retrieves an element from a specified index in the container.
 *
 * Detailed description see in container.h
 */
bool container_at(const container_t *container, void *data, size_t index)
{
  UC_ASSERT(container);
  UC_ASSERT(data);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->at(((linked_list_t *)container->core), data, index)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->at(((vector_t *)container->core), data, index)
                 : false));
}

/**
 * \brief Erases an element at a specified index in the container.
 *
 * Detailed description see in container.h
 */
bool container_erase(container_t *container, size_t index)
{
  UC_ASSERT(container);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->erase(((linked_list_t *)container->core), index)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->erase(((vector_t *)container->core), index)
                 : false));
}

/**
 * \brief Peeks at an element at a specified index in the container without removing it.
 *
 * Detailed description see in container.h
 */
void *container_peek(const container_t *container, size_t index)
{
  UC_ASSERT(container);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->peek(((linked_list_t *)container->core), index)
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->peek(((vector_t *)container->core), index)
                 : NULL));
}

/**
 * \brief Clears all the elements from the container.
 *
 * Detailed description see in container.h
 */
size_t container_clear(const container_t *container)
{
  UC_ASSERT(container);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->clear(((linked_list_t *)container->core))
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->clear(((vector_t *)container->core))
                 : false));
}

/**
 * \brief Returns the number of elements in the container.
 *
 * Detailed description see in container.h
 */
size_t container_size(const container_t *container)
{
  UC_ASSERT(container);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->size(((linked_list_t *)container->core))
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->size(((vector_t *)container->core))
                 : false));
}

/**
 * \brief Returns the size of single element (in bytes).
 *
 * Detailed description see in container.h
 */
size_t container_esize(const container_t *container)
{
  UC_ASSERT(container);

  return ((CONTAINER_LINKED_LIST_BASED == container->type)
            ? ((linked_list_t *)container->core)->esize(((linked_list_t *)container->core))
            : ((CONTAINER_VECTOR_BASED == container->type)
                 ? ((vector_t *)container->core)->esize(((vector_t *)container->core))
                 : false));
}
