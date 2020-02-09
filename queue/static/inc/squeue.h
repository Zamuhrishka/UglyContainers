/**
* \file    		squeue.h
* \author  		Kovalchuk Alexander (roux@yandex.ru)
* \brief		Queue with fixed size.
*
* \warning 		This data structure is not thread-safe!
*/
#pragma once
//_____ I N C L U D E S _______________________________________________________________________
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//_____ Ñ O N F I G S__________________________________________________________________________
#define QUEUE_SIZE                 						32U
//_____ M A C R O S ___________________________________________________________________________
//_____ D E F I N I T I O N ___________________________________________________________________
/**
 * \brief Static queue structure
 */
typedef struct sQueue_t
{
	uint8_t data[QUEUE_SIZE];																	///< array of data
    size_t capacity;																			///< size of queue
    size_t write;																				///< pointer to the write position
    size_t read;																				///< pointer to the read position
    size_t esize;																				///< size in bytes one element
}	squeue_t;
//_____ V A R I A B L E   D E C L A R A T I O N S _____________________________________________
//_____ F U N C T I O N   D E C L A R A T I O N S _____________________________________________
/**
* \brief 	Initialization queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
bool squeue_init(squeue_t *queue, size_t size);

/**
* \brief 	This function check the queue for empty.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
bool squeue_is_empty(const squeue_t *queue);

/**
* \brief 	This function check the queue for full.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
bool squeue_is_full(const squeue_t *queue);

/**
* \brief 	This function return size of queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
size_t squeue_size(const squeue_t *queue);

/**
* \brief 	This function return free size of queue.
*
* \param[in] queue: pointer to queue.
*
* \return 	true/false.
*/
size_t squeue_free_space(const squeue_t *queue);

/**
* \brief 	Add data into queue.
*
* \param[in] queue: pointer to queue.
* \param[in] data: pointer to data for saving in to queue.
*
* \return 	true/false.
*/
bool squeue_enqueue(squeue_t *queue, const void *data);

/**
* \brief 	Get data from queue.
*
* \param[in] queue: pointer to queue.
* \param[out] data: pointer to retrieve data from queue.
*
* \return 	true/false.
*/
bool squeue_denqueue(squeue_t *queue, void *data);
