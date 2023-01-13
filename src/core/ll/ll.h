/**
 * @file ll.h
 * @author learnc.info@gmail.com (https://learnc.info/adt/linked_list.html)
 *          Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief  Double-linked list
 * @date 2023-01-01
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct linked_list_tag;
typedef struct linked_list_tag 				linked_list_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
* @brief 	This function register memory allocation function.
*
* 			The registration function will be use for allocation memory
* 			for vector store.
*
* 			@warning You must register allocation function before call any
* 			function this library.
*
* 			@example vector_alloc_callback_reg(&malloc);
*
* @param  	*custom_malloc[in] - pointer to the memory allocation function.
*
* @return 	none.
*/
void ll_alloc_callback_reg(void* (*custom_malloc)(size_t size));

/**
* @brief 	This function register memory free function.
*
* 			The registration function will be use for free memory
* 			of vector.
*
* 			@warning You must register free function before call any
* 			function this library.
*
* 			@example vector_free_callback_reg(&free);
*
* @param  	*custom_free[in] - pointer to the memory free function.
*
* @return 	none.
*/
void ll_free_callback_reg(void (*custom_free)(void * pointer));

/**
* @brief 	Create new linked list.
*
* @param  	none.
*
* @return 	pointer to new list.
*/
linked_list_t* ll_create(size_t data_size);

/**
* @brief 	Delete list.
*
* @param  	**list[in] - pointer to list.
*
* @return 	true/false.
*/
bool ll_delete(linked_list_t **list);
