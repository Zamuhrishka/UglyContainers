/**
* \file         queue.c
* \author       Kovalchuk Alexander (roux@yandex.ru)
* \brief        This file contains the prototypes functions which use for...
*/
//_____ I N C L U D E S _______________________________________________________
#include "queue.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
//_____ C O N F I G S 
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
/**
 * \brief Static queue structure
 */
struct Queue_t
{
	uint8_t* data;																///< array of data
    size_t write;																///< counter of the write position
    size_t read;																///< counter of the read position
    size_t size;																///< current size of queue
    size_t capacity;															///< max size of queue
    size_t esize;																///< size in bytes for one element
};
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//< Pointer to the memory allocation function
static void* (*mem_alloc_fn)(size_t sizemem) = NULL;

//< Pointer to the memory free function
static void (*mem_free_fn) (void *ptrmem) = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
inline static bool is_callbacks_valid(void)
{
	return ((mem_free_fn != NULL) && (mem_alloc_fn != NULL)) ? true : false;
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
void queue_reg_mem_alloc_cb(void* (*custom_malloc)(size_t sizemem))
{
	assert(custom_malloc);
	mem_alloc_fn = custom_malloc;
}

/**
* This function used to register function for free memory.
*
* Public function defined in queue.h
*/
void queue_reg_mem_free_cb(void (*custom_free)(void * ptrmem))
{	
	assert(custom_free);
	mem_free_fn = custom_free;
}

/**
* This function used to create new queue.
*
* Public function defined in queue.h
*/
queue_t* queue_create(size_t nbm, size_t esize)
{
	queue_t* queue = NULL;

	size_t size_in_bytes = nbm * esize;

	if(!is_callbacks_valid()) {
		return false;
	}

	queue = mem_alloc_fn(sizeof(*queue));
	if (queue == NULL) {
		return NULL;
	}

	queue->data = mem_alloc_fn(size_in_bytes);
	if (queue->data == NULL)
	{
		mem_free_fn((void*)queue);
		return NULL;
	}

	queue->capacity = nbm;
	queue->write = 0;
	queue->read = 0;
	queue->esize = esize;
	queue->size = 0;

	for(size_t i = 0; i < size_in_bytes; i++) {
		queue->data[i] = 0;
	}

	return queue;
}

/**
* This function used to delete queue.
*
* Public function defined in queue.h
*/
void queue_delete(queue_t **queue)
{
	assert(*queue);

	mem_free_fn((*queue)->data);
	mem_free_fn(*queue);
	*queue = NULL;
}

/**
* This function used to check the queue for empty.
*
* Public function defined in queue.h
*/
bool queue_is_empty(const queue_t *queue)
{
	assert(queue);
	return (queue->size == 0) ? true : false;
}

/**
* This function used to check the queue for full.
*
* Public function defined in queue.h
*/
bool queue_is_full(const queue_t *queue)
{
	assert(queue);
	return (queue->size == queue->capacity) ? true : false;
}

/**
* This function return size of queue.
*
* Public function defined in queue.h
*/
size_t queue_size(const queue_t *queue)
{
	assert(queue);
	return queue->size;
}

/**
* This function return free size of queue.
*
* Public function defined in queue.h
*/
size_t queue_free_space(const queue_t *queue)
{
	assert(queue);
	return queue->capacity - queue->size;
}

/**
* This function add data into queue.
*
* Public function defined in queue.h
*/
bool queue_enqueue(queue_t *queue, const void *data)
{
	assert(queue);
	assert(data);

	uint8_t* pData = (uint8_t*)data;
	size_t rawSize = queue->capacity * queue->esize;

	if(queue_is_full(queue)) {
		return false;
	}

	for(size_t i = 0; i < queue->esize; i++)
	{
		queue->data[queue->write] = pData[i];
		queue->write = (queue->write == rawSize - 1ul) ? 0ul: (queue->write + 1ul);
	}

	queue->size++;

	return true;
}

/**
* This function used to get data from queue.
*
* Public function defined in queue.h
*/
bool queue_denqueue(queue_t *queue, void *data)
{
	assert(queue);
	assert(data);

	uint8_t* pData = (uint8_t*)data;
	size_t rawSize = queue->capacity * queue->esize;

	if(queue_is_empty(queue)) {
		return false;
	}

	for(size_t i = 0; i < queue->esize; i++)
	{
		pData[i] = queue->data[queue->read];
		queue->read = (queue->read == rawSize - 1ul) ? 0ul : (queue->read + 1ul);
	}

	queue->size--;

	return true;
}

/**
* This function used to get data from queue without deleting.
*
* Public function defined in queue.h
*/
bool queue_peek(const queue_t *queue, void *data)
{
	assert(queue);
	assert(data);

	uint8_t* pData = (uint8_t*)data;
	uint8_t* pBuffer = &queue->data[queue->read];

	if(queue_is_empty(queue)) {
		return false;
	}

	for(size_t i = 0; i < queue->esize; i++)
	{
		pData[i] = *pBuffer++;
	}

	return true;
}

/**
* This function search data in the queue.
*
* Public function defined in queue.h
*/
bool queue_find(const queue_t *queue, const void *data, bool (*is_equal)(const void*, const void*))
{
	assert(queue);
	assert(data);
	assert(is_equal);

	size_t size = queue_size(queue);

	for(size_t i = 0; i < size; i++)
	{
		if(is_equal((void*)&queue->data[i * queue->esize], data)) {
			return true;
		}
	}

	return false;
}

/**
* This function used to reset queue.
*
* Public function defined in queue.h
*/
void queue_reset(queue_t *queue)
{
	assert(queue);

	size_t rawSize = queue->capacity * queue->esize;

	queue->write = 0;
	queue->read = 0;
	queue->size = 0;

	for(size_t i = 0; i < rawSize; i++) {
		queue->data[i] = 0;
	}
}