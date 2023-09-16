/**
 * \file    queue.c
 * \author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Implementation of a generic queue data structure.
 * \date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes and returns a new queue
 *
 * Detailed description see in queue.h
 */
queue_t* queue_create(size_t esize)
{
  assert(0 != esize);

  queue_t* queue = container_create(esize, CONTAINER_LINKED_LIST_BASED);
  if (NULL == queue)
  {
    return NULL;
  }

  return queue;
}

/**
 * Frees up the memory associated with the queue
 *
 * Detailed description see in queue.h
 */
void queue_delete(queue_t** queue)
{
  assert(*queue);
  assert(queue);

  container_delete((container_t**)queue);
}

/**
 * Checks if the queue is empty.
 *
 * Detailed description see in queue.h
 */
bool queue_empty(const queue_t* queue)
{
  assert(queue);
  size_t size = container_size((container_t*)queue);
  return (size == 0);
}

/**
 * Adds an element to the queue.
 *
 * Detailed description see in queue.h
 */
bool queue_enqueue(queue_t* queue, const void* data)
{
  assert(queue);
  assert(data);

  return container_push_back((container_t*)queue, data);
}

/**
 * Removes an element from the queue and returns it.
 *
 * Detailed description see in queue.h
 */
bool queue_dequeue(queue_t* queue, void* data)
{
  assert(NULL != queue);
  assert(NULL != data);

  return container_pop_front((container_t*)queue, data);
}

/**
 * Retrieves the element from the queue without removing it.
 *
 * Detailed description see in queue.h
 */
bool queue_peek(const queue_t* queue, void* data)
{
  assert(NULL != queue);
  assert(NULL != data);

  return container_at((container_t*)queue, data, 0);
}

/**
 * Returns the number of elements in the queue.
 *
 * Detailed description see in queue.h
 */
size_t queue_size(const queue_t* queue)
{
  assert(NULL != queue);
  return container_size((container_t*)queue);
}

/**
 * Clears all the elements from the queue.
 *
 * Detailed description see in queue.h
 */
bool queue_clear(queue_t* queue)
{
  assert(NULL != queue);
  return container_clear((container_t*)queue);
}
