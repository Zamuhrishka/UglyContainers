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
typedef uint8_t 							lldata_t;
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
void ll_alloc_callback_reg(void* (*custom_malloc)(size_t sizemem));

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
void ll_free_callback_reg(void (*custom_free)(void * ptrmem));

/**
* @brief 	Create new linked list.
*
* @param  	none.
*
* @return 	pointer to new list.
*/
linked_list_t* ll_create(void);

/**
* @brief 	Create linked list from array.
*
* @param  	*list[in] - pointer to list.
* @param  	*arr[in] - pointer to source array.
* @param  	size[in] - size of array.
*
* @return 	true/false.
*/
// bool ll_from_array(linked_list_t *list, const lldata_t *arr, size_t size);

/**
* @brief 	Create array from linked list.
*
* @param  	*list[in] - pointer to list.
* @param  	*arr[out] - pointer to out array.
* @param  	size[in] - size of array.
*
* @return 	true/false.
*/
// bool ll_to_array(linked_list_t *list, lldata_t* arr, size_t size);

/**
* @brief 	Delete list.
*
* @param  	**list[in] - pointer to list.
*
* @return 	true/false.
*/
bool ll_delete(linked_list_t **list);

/**
* @brief 	Add new node on top of list.
*
* @param  	*list[in] - pointer to list.
* @param  	data[in] - data for new node of list.
*
* @return 	true/false.
*/
bool ll_push(linked_list_t *list, lldata_t data);

/**
* @brief 	Delete node on top and return it value.
*
* @param  	*list[in] - pointer to list.
* @param  	*data[out] - value of deleted HEAD node.
*
* @return 	true/false.
*/
bool ll_pop(linked_list_t *list, lldata_t *data);

/**
* @brief 	Add new node to the end of list.
*
* @param  	*list[in] - pointer to list.
* @param  	data[in] - value of new node.
*
* @return 	true/false.
*/
bool ll_enqueue(linked_list_t *list, lldata_t data);

/**
* @brief 	Delete the last node of list.
*
* @param  	*list[in] - pointer to list.
* @param  	*data[out] - value of new node.
*
* @return 	true/false.
*/
bool ll_dequeue(linked_list_t *list, lldata_t *data);

/**
* @brief 	Insert node with value in to list on position index.
*
* @param  	*list[in] - pointer to list.
* @param  	value[in] - value of new node.
* @param  	index[in] - position in list.
*
* @return 	true/false.
*/
bool ll_insert(linked_list_t *list, size_t index, lldata_t value);

/**
* @brief 	Delete node with n position from list. And return it value.
*
* @param  	*list[in] - pointer to list.
* @param  	*value[out] - value of deleted node.
* @param  	index[in] - position in list.
*
* @return 	true/false.
*/
bool ll_extract(linked_list_t *list, size_t index, lldata_t* value);

/**
* @brief 	Calculate size of list.
*
* @param  	*list[in] - pointer to list.
*
* @return 	size of list.
*/
size_t ll_length(const linked_list_t *list);
