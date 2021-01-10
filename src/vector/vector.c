/**********************************************************************************************
* @file    		vector.c
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
//_____ I N C L U D E S _______________________________________________________________________
#include "vector.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//_____ D E F I N I T I O N ___________________________________________________________________
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
//! @brief Structure of vector
//! @{
struct _vector
{
	vDataType_t *data;																			//!pointer to the data array
	size_t size;																				//!size of vector
	size_t capacity;																			//!capacity of vector (available size)
};
//! @}

//!Pointer to the memory allocation function
static void* (*vector_mem_alloc)(size_t sizemem) = NULL;

//!Pointer to the memory free function
static void (*vector_mem_free) (void *ptrmem) = NULL;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
/**
* @brief 	Resize vector.
*
* @param  	*vector[in] - pointer to the resized vector.
*
* @return 	true/false.
*/
__attribute__((always_inline)) inline static bool vector_resize(vector_t *vector)
{
	size_t new_size = vector->size + RESIZE_KOEFF;

	vDataType_t* tmp = (vDataType_t*) vector_mem_alloc(new_size);
	if (tmp == NULL) {
		return false;
	}

	for(size_t i = 0; i < vector->size; i++) {
		tmp[i] = vector->data[i];
	}

	vector_mem_free(vector->data);

	vector->data = tmp;
	vector->capacity = new_size;

	return true;
}
//_____ S T A T I Ñ  F U N C T I O N   D E F I N I T I O N   __________________________________
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
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
void vector_alloc_callback_reg(void* (*custom_malloc)(size_t sizemem))
{
	vector_mem_alloc = custom_malloc;
}

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
void vector_free_callback_reg(void (*custom_free)(void * ptrmem))
{
	vector_mem_free = custom_free;
}

/**
* @brief 	Create new vector.
*
* @param  	size[in] - size of vector.
*
* @return 	pointer to  the creating vector - if ok.
* 		  	NULL - if error occur.
*/
vector_t* vector_create(size_t size)
{
	if(vector_mem_alloc == NULL || vector_mem_free == NULL) {
		return NULL;
	}

	vector_t *vector = (vector_t*) vector_mem_alloc(sizeof(vector_t));
	if (vector == NULL) {
		return NULL;
	}

	vector->size = 0;
	vector->capacity = size + RESIZE_KOEFF;

	vector->data = (vDataType_t*) vector_mem_alloc(vector->capacity);
	if (vector->data == NULL) {
		vector_mem_free((void*)vector);
		return NULL;
	}

	return vector;
}

/**
* @brief 	Delete vector.
*
* @param  	**vector[in] - pointer to the vector.
*
* @return 	none.
*/
void vector_delete(vector_t **vector)
{
	if(*vector == NULL) {
		return;
	}

	vector_mem_free((*vector)->data);
	vector_mem_free(*vector);
	*vector = NULL;
}

/**
* @brief 	Check vector for empty state.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	true - if vector empty and false - if no.
*/
bool vector_empty(const vector_t *vector)
{
	return (vector->size == 0) ? true : false;
}

/**
* @brief 	Return size of vector.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	size of vector.
*/
size_t vector_size(const vector_t *vector)
{
	return vector->size;
}

/**
* @brief 	Return capacity of vector.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	capacity of vector.
*/
size_t vector_capacity(const vector_t *vector)
{
	return vector->capacity;
}

/**
* @brief 	Clear vector.
*
* @param  	*vector[in] - pointer to the vector.
*
* @return 	true/false.
*/
bool vector_clear(vector_t *vector)
{
	if(vector == NULL) {
		return false;
	}

	vDataType_t* tmp = (vDataType_t*) vector_mem_alloc(RESIZE_KOEFF);
	if (tmp == NULL) {
		return false;
	}

	vector_mem_free(vector->data);

	vector->data = tmp;
	vector->size = 0;
	vector->capacity = RESIZE_KOEFF;

	return true;
}

/**
* @brief 	This function read data from index position.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - read data.
* @param  	index[in] - read position.
*
* @return 	true/false.
*/
bool vector_at(const vector_t *vector, vDataType_t *data, size_t index)
{
	if(vector == NULL || vector->size == 0 || index > vector->size) {
		return false;
	}

	*data = vector->data[index];
	return true;
}

/**
* @brief 	This function read and delete data from back of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - read data.
*
* @return 	true/false.
*/
bool vector_pop_back(vector_t *vector, vDataType_t *data)
{
	if(vector == NULL || vector->size == 0) {
		return false;
	}

	vector->size--;
	*data = vector->data[vector->size];
	vector->data[vector->size] = 0;

	return true;
}

/**
* @brief 	This function read and delete data from index position of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - read data.
* @param  	index[in] - index position.
*
* @return 	true/false.
*/
bool vector_extract(vector_t *vector, vDataType_t *data, size_t index)
{
	if(vector == NULL || vector->size == 0 || index > vector->size) {
		return false;
	}

	*data = vector->data[index];
	vector->size--;

	for(size_t i = index; i < vector->size; i++) {
		vector->data[i] = vector->data[i+1];
	}

	return true;
}

/**
* @brief 	This function read and delete data from front of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[out] - read data.
*
* @return 	true/false.
*/
bool vector_pop_front(vector_t *vector, vDataType_t *data)
{
	if(vector == NULL || vector->size == 0) {
		return false;
	}

	*data = vector->data[0];
	vector->size--;

	for(size_t i = 0; i < vector->size; i++) {
		vector->data[i] = vector->data[i+1];
	}

	return true;
}

/**
* @brief 	This function delete data from index position.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	*data[in] - read data.
*
* @return 	true/false.
*/
bool vector_erase(vector_t *vector, size_t index)
{
	if(vector == NULL || vector->size == 0 || index > vector->size) {
		return false;
	}

	for(size_t i = index; i < vector->size; i++) {
		vector->data[i] = vector->data[i+1];
	}

	vector->size--;

	return true;
}

/**
* @brief 	This function added data into end of vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	data[in] - data.
*
* @return 	true/false.
*/
bool vector_append(vector_t *vector, vDataType_t data)
{
	if(vector == NULL) {
		return false;
	}

	if(vector->size >= vector->capacity)
	{
		if(vector_resize(vector) != true) {
			return false;
		}
	}

	vector->data[vector->size] = data;
	vector->size++;
	return true;
}

/**
* @brief 	This function added data into index position into vector.
*
* @param  	*vector[in] - pointer to the vector.
* @param  	data[in] - data.
* @param  	index[in] - position.
*
* @return 	true/false.
*/
bool vector_insert(vector_t *vector, vDataType_t data, size_t index)
{
	if(vector == NULL || index > vector->size) {
		return false;
	}

	if(vector->size >= vector->capacity)
	{
		if(vector_resize(vector) != true) {
			return false;
		}
	}

	for(int32_t i = vector->size; i >= (int32_t)index; --i) {
		vector->data[i+1] = vector->data[i];
	}

	vector->data[index] = data;
	vector->size++;
	return true;

}
