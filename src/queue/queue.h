/**
* \file         queue.h
* \author       Kovalchuk Alexander (roux@yandex.ru)
* \brief        This file contains the prototypes functions which use for...
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
//_____ D E F I N I T I O N S _________________________________________________
struct Queue_t;
typedef struct Queue_t queue_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
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
void queue_reg_mem_alloc_cb(void* (*custom_malloc)(size_t sizemem));

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
void queue_reg_mem_free_cb(void (*custom_free)(void * ptrmem));

/**
* \brief 	Create new queue.
*
* \param[in] nbm: number of elements in queue.
* \param[in] esize: size of one element of queue.
*
* \return 	pointer to new queue or NULL.
*/
queue_t* queue_create(size_t nbm, size_t esize);

/**
* \brief 	Delete queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	none.
*/
void queue_delete(queue_t **queue);

/**
* \brief 	This function check the queue for empty.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
bool queue_is_empty(const queue_t *queue);

/**
* \brief 	This function check the queue for full.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
bool queue_is_full(const queue_t *queue);

/**
* \brief 	This function return size of queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
size_t queue_size(const queue_t *queue);

/**
* \brief 	This function return free size of queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
size_t queue_free_space(const queue_t *queue);

/**
* \brief 	Add data into queue.
*
* \param[in] queue: pointer to queue.
* \param[in] data: pointer to data for saving in to queue.
*
* \return 	true/false.
*/
bool queue_enqueue(queue_t *queue, const void *data);

/**
* \brief 	Get data from queue.
*
* \param[in] queue: pointer to queue.
* \param[out] data: pointer to retrieve data from queue.
*
* \return 	true/false.
*/
bool queue_denqueue(queue_t *queue, void *data);

/**
* \brief 	This function used to get data from queue without deleting.
*
* \param[in] queue: pointer to queue.
* \param[out] data: pointer to retrieve data from queue.
*
* \return 	true/false.
*/
bool queue_peek(const queue_t *queue, void *data);

/**
* \brief 	This function search data in the queue.
*
* \param[in] queue: pointer to queue.
* \param[in] data: pointer to retrieve data from queue.
* \param[in] is_equal: callback function for compare data.
*
* \return 	true - if data find;
* 			false - if data not find.
*/
bool queue_find(const queue_t *queue, const void *data, bool (*is_equal)(const void*, const void*));

/**
* \brief 	This function used to reset queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
void queue_reset(queue_t *queue);

/* C++ detection */
#ifdef __cplusplus
}
#endif
