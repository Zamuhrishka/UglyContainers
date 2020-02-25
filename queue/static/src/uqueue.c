/**
* \file    		template.c
* \author  		Kovalchuk Alexander
* \email  		roux@yandex.ru
* \brief   		This file contains the prototypes functions which use for...
*/

/*
 * Copyright (c) year Alexander KOVALCHUK
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:          Alexander KOVALCHUK <roux@yandex.ru>
 */
//_____ I N C L U D E S _______________________________________________________
#include "uqueue.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N ___________________________________________________
#ifdef UQUEUE_STATIC_MODE
/**
 * \brief Static queue structure
 */
struct UQueue_t
{
	uint8_t data[UQUEUE_SIZE_IN_BYTES];															///< array of data
    size_t write;																				///< pointer to the write position
    size_t read;																				///< pointer to the read position
    size_t size;																				///< size of queue
    size_t capacity;																			///< max size of queue
    size_t esize;																				///< size in bytes one element
    uqueue_is_equal_fn_t compare_cb;
};
#else
/**
 * \brief queue structure
 */
struct UQueue_t
{
	uint8_t* data;																				///< array of data
    size_t write;																				///< pointer to the write position
    size_t read;																				///< pointer to the read position
    size_t size;																				///< current size of queue
    size_t capacity;																			///< max size of queue
    size_t esize;																				///< size in bytes one element
    uqueue_is_equal_fn_t compare_cb;
};
#endif
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________
//!Pointer to the memory allocation function
static void* (*mem_alloc_fn)(size_t sizemem) = NULL;

//!Pointer to the memory free function
static void (*mem_free_fn) (void *ptrmem) = NULL;

#ifdef UQUEUE_STATIC_MODE
static uqueue_t pool[MAX_UQUEUES_IN_POOL] = {0};
static size_t counter = 0;
#endif
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________
inline static bool is_callbacks_valid(void)
{
	return ((mem_free_fn != NULL) && (mem_alloc_fn != NULL)) ? true : false;
}
//_____ S T A T I C  F U N C T I O N   D E F I N I T I O N   __________________
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________
/**
* This function used to register function for alloc memory.
*
* Public function defined in uqueue.h
*/
void uqueue_reg_mem_alloc_cb(void* (*custom_malloc)(size_t sizemem))
{
	assert(custom_malloc);
	mem_alloc_fn = custom_malloc;
}

/**
* This function used to register function for free memory.
*
* Public function defined in uqueue.h
*/
void uqueue_reg_mem_free_cb(void (*custom_free)(void * ptrmem))
{
	assert(custom_free);
	mem_free_fn = custom_free;
}

/**
* This function used to register function for compare queue elements.
*
* Public function defined in uqueue.h
*/
void uqueue_reg_compare_cb(uqueue_t *queue, uqueue_is_equal_fn_t custom_compare)
{
	assert(queue);
	assert(custom_compare);
    queue->compare_cb = custom_compare;
}

/**
* This function used to create new queue.
*
* Public function defined in uqueue.h
*/
uqueue_t* uqueue_create(size_t capacity, size_t esize, const uqueue_is_equal_fn_t custom_compare)
{
	uqueue_t *queue = NULL;
	size_t rawSize = capacity * esize;

#ifndef UQUEUE_STATIC_MODE
	if(!is_callbacks_valid()) {
		return false;
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
	queue->compare_cb = custom_compare;

	for(size_t i = 0; i < rawSize; i++) {
		queue->data[i] = 0;
	}
#else
	if(counter < MAX_UQUEUES_IN_POOL)
	{
		queue = &pool[counter++];

		queue->write = 0;
		queue->read = 0;
		queue->capacity = (rawSize > UQUEUE_SIZE_IN_BYTES) ? UQUEUE_SIZE_IN_BYTES : capacity;
		queue->esize = esize;
		queue->size = 0;
		queue->compare_cb = custom_compare;

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
* Public function defined in uqueue.h
*/
void uqueue_delete(uqueue_t **queue)
{
#ifndef UQUEUE_STATIC_MODE
	assert(*queue);

	mem_free_fn((*queue)->data);
	mem_free_fn(*queue);
	*queue = NULL;
#endif
}

/**
* This function used to check the queue for empty.
*
* Public function defined in uqueue.h
*/
bool uqueue_is_empty(const uqueue_t *queue)
{
	assert(queue);

	if(queue->size == 0) {
		return true;
	}

	return false;
}

/**
* This function used to check the queue for full.
*
* Public function defined in uqueue.h
*/
bool uqueue_is_full(const uqueue_t *queue)
{
	assert(queue);

	if(queue->size == queue->capacity) {
		return true;
	}

	return false;
}

/**
* This function return size of queue.
*
* Public function defined in uqueue.h
*/
size_t uqueue_size(const uqueue_t *queue)
{
	assert(queue);
	return queue->size;
}

/**
* This function return free size of queue.
*
* Public function defined in uqueue.h
*/
size_t uqueue_free_space(const uqueue_t *queue)
{
	assert(queue);
	return queue->capacity - queue->size;
}

/**
* This function add data into queue.
*
* Public function defined in uqueue.h
*/
bool uqueue_enqueue(uqueue_t *queue, const void *data)
{
	assert(queue);
	assert(data);

	size_t size = 0;
	uint8_t* pData = (uint8_t*)data;
	size_t rawSize = queue->capacity * queue->esize;

	if(queue->compare_cb == NULL) {
		return false;
	}

	if(uqueue_is_full(queue)) {
		return false;
	}

	size = uqueue_size(queue);

	for(size_t i = 0; i < size; i++)
	{
		if(queue->compare_cb((void*)&queue->data[i * queue->esize], data)) {
			return true;
		}
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
* Public function defined in uqueue.h
*/
bool uqueue_denqueue(uqueue_t *queue, void *data)
{
	assert(queue);
	assert(data);

	uint8_t* pData = (uint8_t*)data;
	size_t rawSize = queue->capacity * queue->esize;

	if(uqueue_is_empty(queue)) {
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
* Public function defined in uqueue.h
*/
bool uqueue_peek(uqueue_t *queue, void *data)
{
	assert(queue);
	assert(data);

	uint8_t* pData = (uint8_t*)data;
	uint8_t* pBuffer = &queue->data[queue->read];

	if(uqueue_is_empty(queue)) {
		return false;
	}

	for(size_t i = 0; i < queue->esize; i++)
	{
		pData[i] = pBuffer++;
	}

	return true;
}

/**
* This function used to reset queue.
*
* Public function defined in uqueue.h
*/
void uqueue_flush(uqueue_t *queue)
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
