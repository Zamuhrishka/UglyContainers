/**********************************************************************************************
* @file    		vector.h
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @brief		Vectors are sequence containers representing arrays that can change in size.
* 				Internally, vectors use a dynamically allocated array to store their elements.
* 				This array may need to be reallocated in order to grow in size when new elements
* 				are inserted, which implies allocating a new array and moving all elements to it.
* 				This is a relatively expensive task in terms of processing time, and thus, vectors
* 				do not reallocate each time an element is added to the container.
*
* @warning 		This data structure is not thread-safe!
***********************************************************************************************/
#pragma once
//_____ I N C L U D E S _______________________________________________________________________
#include "stdint.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//_____ Ñ O N F I G S__________________________________________________________________________
#define RESIZE_KOEFF 								(32ul)
typedef uint8_t 									vDataType_t;
//_____ M A C R O S ___________________________________________________________________________
//_____ D E F I N I T I O N ___________________________________________________________________
//_____ V A R I A B L E   D E C L A R A T I O N S _____________________________________________
typedef struct _vector 						vector_t;
//_____ F U N C T I O N   D E C L A R A T I O N S _____________________________________________
/**
* @brief 	This function register memory allocation function.
*
* 			The registration function will be use for allocation memmory
* 			for vector store.
*
* 			@warning You must register allocation function before call any
* 			function this library.
*
* 			@example ector_alloc_callback_reg(&malloc);
*
* @param  	*custom_malloc[in] - pointer to the memory allocation function.
*
* @return 	none.
*/
void vector_alloc_callback_reg(void* (*custom_malloc)(size_t sizemem));

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
void vector_free_callback_reg(void (*custom_free)(void * ptrmem));

/**
* @brief 	Create new vector.
*
* @param  	size[in] - size of vector.
*
* @return 	pointer to  the creating vector - if ok.
* 		  	NULL - if error occur.
*/
vector_t* vector_create(size_t size);

/**
* @brief 	Delete vector.
*
* @param  	**vector[in] - pointer to the vector.
*
* @return 	none.
*/
void vector_delete(vector_t **vector);

/**
* @brief 	Check vector for empty state.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	true - if vector empty and false - if no.
*/
bool vector_empty(const vector_t *vector);

/**
* @brief 	Return size of vector.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	size of vector.
*/
size_t vector_size(const vector_t *vector);

/**
* @brief 	Return capacity of vector.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	capacity of vector.
*/
size_t vector_capacity(const vector_t *vector);

/**
* @brief 	Clear vector.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	true/false.
*/
bool vector_clear(vector_t *vector);

/**
* @brief 	This function read data from index position.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - read data.
* @param  	index[in] - read position.
*
* @return 	true/false.
*/
bool vector_at(const vector_t *vector, vDataType_t *data, size_t index);

/**
* @brief 	This function read and delete data from back of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - read data.
*
* @return 	true/false.
*/
bool vector_pop_back(vector_t *vector, vDataType_t *data);

/**
* @brief 	This function read and delete data from index position of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - read data.
* @param  	index[in] - index position.
*
* @return 	true/false.
*/
bool vector_extract(vector_t *vector, vDataType_t *data, size_t index);

/**
* @brief 	This function read and delete data from front of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - readed data.
*
* @return 	true/false.
*/
bool vector_pop_front(vector_t *vector, vDataType_t *data);

/**
* @brief 	This function delete data from index position.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[in] - read data.
*
* @return 	true/false.
*/
bool vector_erase(vector_t *vector, size_t index);

/**
* @brief 	This function added data into end of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	data[in] - data.
*
* @return 	true/false.
*/
bool vector_append(vector_t *vector, vDataType_t data);

/**
* @brief 	This function added data into index position into vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	data[in] - data.
* @param  	index[in] - position.
*
* @return 	true/false.
*/
bool vector_insert(vector_t *vector, vDataType_t data, size_t index);
