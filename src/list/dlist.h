/**********************************************************************************************
* @file    		slinked_list.h
* @author  		learnc.info@gmail.com
* @website		https://learnc.info/adt/linked_list.html
* @correct 		alexander.kovalchuk@promwad.com
* @brief		Single-linked list realization.
***********************************************************************************************/
#pragma once
/* C++ detection */
#ifdef __cplusplus
	extern "C" {
#endif
//_____ I N C L U D E S ________________________________________________________________________
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
//_____ Ñ O N F I G S___________________________________________________________________________
typedef uint8_t 							dListData_t;
//_____ M A C R O S ____________________________________________________________________________
//_____ D E F I N I T I O N ____________________________________________________________________
//_____ V A R I A B L E   D E C L A R A T I O N S ______________________________________________
typedef struct _DLinkedList 				dLinkedList_t;
//_____ F U N C T I O N   D E C L A R A T I O N S ______________________________________________
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
void dlist_alloc_callback_reg(void* (*custom_malloc)(size_t sizemem));

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
void dlist_free_callback_reg(void (*custom_free)(void * ptrmem));

/**
* @brief 	Create new linked list.
*
* @param  	none.
*
* @return 	pointer to new list.
*/
dLinkedList_t* dlist_create(void);

/**
* @brief 	Create linked list from array.
*
* @param  	*list[in] - pointer to list.
* @param  	*arr[in] - pointer to source array.
* @param  	size[in] - size of array.
*
* @return 	true/false.
*/
bool dlist_from_array(dLinkedList_t *list, const dListData_t *arr, size_t size);

/**
* @brief 	Create array from linked list.
*
* @param  	*list[in] - pointer to list.
* @param  	*arr[out] - pointer to out array.
* @param  	size[in] - size of array.
*
* @return 	true/false.
*/
bool dlist_to_array(dLinkedList_t *list, dListData_t* arr, size_t size);

/**
* @brief 	Delete list.
*
* @param  	**list[in] - pointer to list.
*
* @return 	true/false.
*/
bool dlist_delete(dLinkedList_t **list);

/**
* @brief 	Add new node on top of list.
*
* @param  	*list[in] - pointer to list.
* @param  	data[in] - data for new node of list.
*
* @return 	true/false.
*/
bool dlist_push(dLinkedList_t *list, dListData_t data);

/**
* @brief 	Delete node on top and return it value.
*
* @param  	*list[in] - pointer to list.
* @param  	*data[out] - value of deleted HEAD node.
*
* @return 	true/false.
*/
bool dlist_pop(dLinkedList_t *list, dListData_t *data);

/**
* @brief 	Add new node to the end of list.
*
* @param  	*list[in] - pointer to list.
* @param  	data[in] - value of new node.
*
* @return 	true/false.
*/
bool dlist_enqueue(dLinkedList_t *list, dListData_t data);

/**
* @brief 	Delete the last node of list.
*
* @param  	*list[in] - pointer to list.
* @param  	*data[out] - value of new node.
*
* @return 	true/false.
*/
bool dlist_dequeue(dLinkedList_t *list, dListData_t *data);

/**
* @brief 	Insert node with value in to list on position index.
*
* @param  	*list[in] - pointer to list.
* @param  	value[in] - value of new node.
* @param  	index[in] - position in list.
*
* @return 	true/false.
*/
bool dlist_insert(dLinkedList_t *list, size_t index, dListData_t value);

/**
* @brief 	Delete node with n position from list. And return it value.
*
* @param  	*list[in] - pointer to list.
* @param  	*value[out] - value of deleted node.
* @param  	index[in] - position in list.
*
* @return 	true/false.
*/
bool dlist_extract(dLinkedList_t *list, size_t index, dListData_t* value);

/**
* @brief 	Calculate size of list.
*
* @param  	*list[in] - pointer to list.
*
* @return 	size of list.
*/
size_t dlist_length(const dLinkedList_t *list);

/* C++ detection */
#ifdef __cplusplus
}
#endif

