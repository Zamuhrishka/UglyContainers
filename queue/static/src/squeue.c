// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
* @file    		squeue.c
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @brief		Queue with fixed size.
*
* @warning 		This data structure is not thread-safe!
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
//_____ I N C L U D E S ______________________________________________________
#include "squeue.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//_____ C O N F I G S  _______________________________________________________
//_____ D E F I N I T I O N __________________________________________________
//_____ M A C R O S __________________________________________________________
//_____ V A R I A B L E   D E F I N I T I O N  _______________________________
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   ________________
//_____ S T A T I Ñ  F U N C T I O N   D E F I N I T I O N   _________________
//_____ F U N C T I O N   D E F I N I T I O N   ______________________________
/**
* This function used to initialization queue.
*
* Public function defined in squeue.h
*/
bool squeue_init(squeue_t *queue, size_t size)
{
	if(queue == NULL) {
		return false;
	}

	queue->capacity = 0;
	queue->write = 0;
	queue->read = 0;
	queue->esize = size;

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		queue->data[i] = 0;
	}

	return true;
}

/**
* This function used to check the queue for empty.
*
* Public function defined in squeue.h
*/
bool squeue_is_empty(const squeue_t *queue)
{
	if(queue->capacity == 0) {
		return true;
	}

	return (((queue->capacity - queue->esize) >= queue->capacity)) ? true : false;
}

/**
* This function used to check the queue for full.
*
* Public function defined in squeue.h
*/
bool squeue_is_full(const squeue_t *queue)
{
	if(queue->capacity == QUEUE_SIZE) {
		return true;
	}

	return (queue->capacity + queue->esize > QUEUE_SIZE) ? true : false;
}

/**
* This function return size of queue.
*
* Public function defined in squeue.h
*/
size_t squeue_size(const squeue_t *queue)
{
	return queue->capacity/queue->esize;
}

/**
* This function return free size of queue.
*
* Public function defined in squeue.h
*/
size_t squeue_free_space(const squeue_t *queue)
{
	return QUEUE_SIZE - queue->capacity/queue->esize;
}

/**
* This function add data into queue.
*
* Public function defined in squeue.h
*/
bool squeue_enqueue(squeue_t *queue, const void *data)
{
	uint8_t* pData = (uint8_t*)data;

	if(queue == NULL || data == NULL) {
		return false;
	}

	if(squeue_is_full(queue)) {
		return false;
	}

	for(size_t i = 0; i < queue->esize; i++)
	{
		queue->data[queue->write] = pData[i];
		queue->capacity++;
		queue->write = (queue->write == QUEUE_SIZE - 1ul) ? 0ul: (queue->write + 1ul);
	}

	return true;
}

/**
* This function used to get data from queue.
*
* Public function defined in squeue.h
*/
bool squeue_denqueue(squeue_t *queue, void *data)
{
	uint8_t* pData = (uint8_t*)data;

	if(queue == NULL || data == NULL) {
		return false;
	}

	if(squeue_is_empty(queue)) {
		return false;
	}

	for(size_t i = 0; i < queue->esize; i++)
	{
		pData[i] = queue->data[queue->read];
		queue->capacity--;
		queue->read = (queue->read == QUEUE_SIZE - 1ul) ? 0ul : (queue->read + 1ul);
	}

	return true;
}

/**
* This function used to get data from queue without deleting.
*
* Public function defined in squeue.h
*/
bool squeue_peek(squeue_t *queue, void *data)
{
	uint8_t* pData = (uint8_t*)data;

	if(queue == NULL || data == NULL) {
		return false;
	}

	if(squeue_is_empty(queue)) {
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
* Public function defined in squeue.h
*/
void squeue_flush(squeue_t *queue)
{
	queue->write = 0;
	queue->read = 0;
	queue->capacity = 0;

	for(size_t i = 0; i < queue->capacity; i++) {
		queue->data[i] = 0;
	}
}
