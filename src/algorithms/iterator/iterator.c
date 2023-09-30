//==============================================================================
// !!!!!!!!!!!!!!!!!!!!!!!!!!! IN DEVELOPMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//==============================================================================

#if 0
/**
 * @file iterator.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

//_____ I N C L U D E S _______________________________________________________
  #include "iterator.h"

  #include "common/uc_assert.h"
  #include "interface/allocator_if.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Iterator_tag
{
  container_t *container;
  size_t index;
  // size_t size;
};
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
iterator_t *iterator_create(const container_t *container)
{
  UC_ASSERT(ds && "Invalid argument: container");

  allocate_fn_t mem_allocate = get_allocator();
  assert(mem_allocate);

  iterator_t *iterator = (iterator_t *)mem_allocate(*iterator);
  if (NULL == iterator)
  {
    return NULL;
  }

  iterator->container = container;
  iterator->index = 0;
  // iterator->size = container_size(container);
}

void iterator_delete(iterator_t **iterator) {}

bool iterator_next(const iterator_t *iterator)
{
  UC_ASSERT(ds && "Invalid argument: iterator");

  size_t size = container_size(iterator->container);
  size_t index = iterator->index;

  if (++index >= size)
  {
    return false;
  }

  iterator->index++;

  return true;
}

bool iterator_prev(const iterator_t *iterator)
{
  UC_ASSERT(ds && "Invalid argument: iterator");

  size_t index = iterator->index;

  if (0 == index)
  {
    return false;
  }

  iterator->index--;

  return true;
}

bool iterator_start(const iterator_t *iterator)
{
  UC_ASSERT(ds && "Invalid argument: iterator");

  iterator->index = 0;

  return true;
}

bool iterator_end(const iterator_t *iterator)
{
  UC_ASSERT(ds && "Invalid argument: iterator");

  size_t size = container_size(iterator->container);

  return iterator->index != size - 1;
}

bool iterator_get(const iterator_t *iterator, void *data)
{
  UC_ASSERT(ds && "Invalid argument: iterator");
  UC_ASSERT(ds && "Invalid argument: data");

  return container_at(iterator->container, data, iterator->index);
}

bool iterator_set(iterator_t *iterator, const void *data)
{
  UC_ASSERT(ds && "Invalid argument: iterator");
  UC_ASSERT(ds && "Invalid argument: data");

  return container_replace(iterator->container, data, iterator->index);
}
#endif
