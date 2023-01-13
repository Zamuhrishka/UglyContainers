/**
 * @file sll.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief 
 * @date 2023-01-12
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Sll_tag;
typedef struct Sll_tag  				sll_t;
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
void sll_alloc_callback_reg(void* (*custom_malloc)(size_t size));

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
void sll_free_callback_reg(void (*custom_free)(void * pointer));

/**
* @brief 	Create new linked list.
*
* @param  	none.
*
* @return 	pointer to new list.
*/
sll_t* sll_create(size_t data_size);

/**
* @brief 	Delete list.
*
* @param  	**list[in] - pointer to list.
*
* @return 	true/false.
*/
bool sll_delete(sll_t **list);



bool sll_push_front(sll_t* ll, const void* data);
bool sll_pop_front(sll_t* ll, void* data);
bool sll_push_back(sll_t* ll, const void* data);
bool sll_pop_back(sll_t* ll, void* data);
bool sll_insert(sll_t* ll, const void* data, size_t position);
bool sll_erase(sll_t* ll, size_t position);