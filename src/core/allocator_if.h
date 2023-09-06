/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "stdbool.h"
#include "stdint.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
typedef void* (*allocate_fn_t)(size_t size);
typedef void (*free_fn_t)(void* pointer);
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
void allocation_cb_register(allocate_fn_t alloc_cb);

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
void free_cb_register(free_fn_t free_cb);
allocate_fn_t get_allocator(void);
free_fn_t get_free(void);
bool is_allocator_valid(void);
