/**
* \file    		template.h
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

#pragma once

/* C++ detection */
#ifdef __cplusplus
	extern "C" {
#endif
//_____ I N C L U D E S _______________________________________________________
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N ___________________________________________________
struct UQueue_t;
typedef struct UQueue_t uqueue_t;

typedef bool (*uqueue_is_equal_fn_t)(const void*, const void*);
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E   D E C L A R A T I O N S _____________________________
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________
//_____ S T A T I C  F U N C T I O N   D E F I N I T I O N   __________________
//_____ F U N C T I O N   D E C L A R A T I O N S _____________________________
/**
* \brief 	This function register memory allocation function.
*
* 			The registration function will be use for allocate memory
* 			for queue.
*
* 			@warning You must register allocation function before call any
* 			function this library.
*
* 			@example queue_reg_mem_alloc_cb(&malloc);
*
* \param[in] custom_malloc: pointer to the memory allocation function.
*
* \return 	none.
*/
void uqueue_reg_mem_alloc_cb(void* (*custom_malloc)(size_t sizemem));

/**
* \brief 	This function register memory free function.
*
* 			The registration function will be use for free memory
* 			of queue.
*
* 			@warning You must register free function before call any
* 			function this library.
*
* 			@example queue_reg_mem_free_cb(&free);
*
* \param[in] custom_free: pointer to the memory free function.
*
* \return 	none.
*/
void uqueue_reg_mem_free_cb(void (*custom_free)(void * ptrmem));

/**
* \brief 	This function register callback function for compare queue element.
*
* 			@warning You must register this function before call any
* 			function this library.
*
* \uqueue[in] uqueue: pointer to queue.
* \param[in] custom_compare: pointer to the callback function.
*
* \return 	none.
*/
void uqueue_reg_compare_cb(uqueue_t *uqueue, uqueue_is_equal_fn_t custom_compare);

/**
* \brief 	Create new queue.
*
* \param[in] capacity: size of queue.
* \param[in] nodeSize: size of element of queue.
*
* \return 	pointer to new queue or NULL.
*/
uqueue_t* uqueue_create(size_t capacity, size_t esize, const uqueue_is_equal_fn_t custom_compare);

/**
* \brief 	Delete queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	none.
*/
void uqueue_delete(uqueue_t **uqueue);

/**
* \brief 	This function check the queue for empty.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
bool uqueue_is_empty(const uqueue_t *uqueue);

/**
* \brief 	This function check the queue for full.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
bool uqueue_is_full(const uqueue_t *uqueue);

/**
* \brief 	This function return size of queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
size_t uqueue_size(const uqueue_t *uqueue);

/**
* \brief 	This function return free size of queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
size_t uqueue_free_space(const uqueue_t *uqueue);

/**
* \brief 	Add data into queue.
*
* \param[in] queue: pointer to queue.
* \param[in] data: pointer to data for saving in to queue.
*
* \return 	true/false.
*/
bool uqueue_enqueue(uqueue_t *uqueue, const void *data);

/**
* \brief 	Get data from queue.
*
* \param[in] queue: pointer to queue.
* \param[out] data: pointer to retrieve data from queue.
*
* \return 	true/false.
*/
bool uqueue_denqueue(uqueue_t *uqueue, void *data);

/**
* \brief 	This function used to get data from queue without deleting.
*
* \param[in] queue: pointer to queue.
* \param[out] data: pointer to retrieve data from queue.
*
* \return 	true/false.
*/
bool uqueue_peek(uqueue_t *uqueue, void *data);

/**
* \brief 	This function used to reset queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
void uqueue_flush(uqueue_t *uqueue);

/* C++ detection */
#ifdef __cplusplus
}
#endif
