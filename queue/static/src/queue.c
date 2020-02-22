// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
* @file    		queue.c
* @author  		Kovalchuk Alexander roux@yandex.ru
* @brief		Queue with fixed size.
*
* @warning 		This data structure is not thread-safe!
*/
//_____ I N C L U D E S _______________________________________________________________________
#include "queue.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//_____ C O N F I G S  ________________________________________________________________________
//_____ D E F I N I T I O N ___________________________________________________________________
#ifdef QUEUE_STATIC_MODE
/**
 * \brief Static queue structure
 */
struct Queue_t
{
	uint8_t data[QUEUE_SIZE_IN_BYTES];															///< array of data
    size_t write;																				///< pointer to the write position
    size_t read;																				///< pointer to the read position
    size_t size;																				///< size of queue
    size_t capacity;																			///< max size of queue
    size_t esize;																				///< size in bytes one element
};
#else
/**
 * \brief Static queue structure
 */
struct Queue_t
{
	uint8_t* data;																				///< array of data
    size_t write;																				///< pointer to the write position
    size_t read;																				///< pointer to the read position
    size_t size;																				///< current size of queue
    size_t capacity;																			///< max size of queue
    size_t esize;																				///< size in bytes one element
};
#endif
//_____ M A C R O S ___________________________________________________________________________
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
//!Pointer to the memory allocation function
static void* (*mem_alloc_fn)(size_t sizemem) = NULL;

//!Pointer to the memory free function
static void (*mem_free_fn) (void *ptrmem) = NULL;

#ifdef QUEUE_STATIC_MODE
static queue_t pool[MAX_QUEUES_IN_POOL] = {0};
static size_t counter = 0;
#endif
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
//_____ S T A T I C  F U N C T I O N   D E F I N I T I O N   __________________________________
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
void queue_reg_mem_alloc_cb(void* (*custom_malloc)(size_t sizemem))
{
	if(custom_malloc == NULL) {
		return;
	}

	mem_alloc_fn = custom_malloc;
}

/**
* This function used to register function for free memory.
*
* Public function defined in queue.h
*/
void queue_reg_mem_free_cb(void (*custom_free)(void * ptrmem))
{
	if(custom_free == NULL) {
		return;
	}

	mem_free_fn = custom_free;
}

/**
* This function used to create new queue.
*
* Public function defined in queue.h
*/
queue_t* queue_create(size_t capacity, size_t esize)
{
	queue_t *queue = NULL;
	size_t rawSize = capacity * esize;

#ifndef QUEUE_STATIC_MODE
	if((mem_alloc_fn == NULL) || (mem_free_fn == NULL)) {
		return NULL;
	}

	queue = mem_alloc_fn(sizeof(*queue));
	if (queue == NULL) {
		return NULL;
	}

	queue->data = mem_alloc_fn(rawSize);
	if (queue->data == NULL)
	{
		mem_free_fn((void*)queue);
		return NULL;
	}

	queue->write = 0;
	queue->read = 0;
	queue->capacity = capacity;
	queue->esize = esize;
	queue->size = 0;

	for(size_t i = 0; i < rawSize; i++) {
		queue->data[i] = 0;
	}
#else
	if(counter < MAX_QUEUES_IN_POOL)
	{
		queue = &pool[counter++];
		queue->write = 0;
		queue->read = 0;
		queue->capacity = (rawSize > QUEUE_SIZE_IN_BYTES) ? QUEUE_SIZE_IN_BYTES : capacity;
		queue->esize = esize;
		queue->size = 0;

		for(size_t i = 0; i < rawSize; i++) {
			queue->data[i] = 0;
		}
	}

#endif

	return queue;
}

/**
* This function used to delete queue.
*
* Public function defined in queue.h
*/
void queue_delete(queue_t **queue)
{
#ifndef QUEUE_STATIC_MODE
	if(*queue == NULL) {
		return;
	}

	mem_free_fn((*queue)->data);
	mem_free_fn(*queue);
	*queue = NULL;
#endif
}

/**
* This function used to check the queue for empty.
*
* Public function defined in queue.h
*/
bool queue_is_empty(const queue_t *queue)
{
	if(queue->size == 0) {
		return true;
	}

	return false;
}

/**
* This function used to check the queue for full.
*
* Public function defined in queue.h
*/
bool queue_is_full(const queue_t *queue)
{
	if(queue->size == queue->capacity) {
		return true;
	}

	return false;
}

/**
* This function return size of queue.
*
* Public function defined in queue.h
*/
size_t queue_size(const queue_t *queue)
{
	return queue->size;
}

/**
* This function return free size of queue.
*
* Public function defined in queue.h
*/
size_t queue_free_space(const queue_t *queue)
{
	return queue->capacity - queue->size;
}

/**
* This function add data into queue.
*
* Public function defined in queue.h
*/
bool queue_enqueue(queue_t *queue, const void *data)
{
	uint8_t* pData = (uint8_t*)data;
	size_t rawSize = queue->capacity * queue->esize;

	if(queue == NULL || data == NULL) {
		return false;
	}

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
	uint8_t* pData = (uint8_t*)data;
	size_t rawSize = queue->capacity * queue->esize;

	if(queue == NULL || data == NULL) {
		return false;
	}

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
bool queue_peek(queue_t *queue, void *data)
{
	uint8_t* pData = (uint8_t*)data;

	if(queue == NULL || data == NULL) {
		return false;
	}

	if(mem_free_fn == NULL || mem_alloc_fn == NULL) {
		return false;
	}

	if(queue_is_empty(queue)) {
		return false;
	}

	for(size_t i = 0; i < queue->esize; i++)
	{
		pData[i] = queue->data[i];
	}

	return true;
}

/**
* This function used to reset queue.
*
* Public function defined in queue.h
*/
void queue_flush(queue_t *queue)
{
	size_t rawSize = queue->capacity * queue->esize;

	queue->write = 0;
	queue->read = 0;
	queue->size = 0;

	for(size_t i = 0; i < rawSize; i++) {
		queue->data[i] = 0;
	}
}
