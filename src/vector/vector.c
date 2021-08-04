/**
* \file         vector.c
* \author       Kovalchuk Alexander (roux@yandex.ru)
* \brief        This file contains the prototypes functions which use for...
*/
//_____ I N C L U D E S _______________________________________________________
#include "vector.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
//_____ C O N F I G S  ________________________________________________________
#define RESIZE_FACTOR 						(32u)
//_____ D E F I N I T I O N S _________________________________________________
//< @brief Structure of vector
//< @{
struct _vector
{
	uint8_t* data;																///< array of data
    size_t size;																///< current size
    size_t capacity;															///< max size
    size_t esize;																///< size in bytes for one element
};
//< @}
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//< Pointer to the memory allocation function
static void* (*vector_mem_alloc)(size_t sizemem) = NULL;

//< Pointer to the memory free function
static void (*vector_mem_free) (void *ptrmem) = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
__attribute__((always_inline)) inline static bool vector_resize(vector_t *vector)
{
	size_t new_size = vector->size + RESIZE_FACTOR;

	uint8_t* tmp = (uint8_t*) vector_mem_alloc(new_size * vector->esize);
	if (tmp == NULL) {
		return false;
	}

	size_t size_in_bytes = vector->size * vector->esize;

	for(size_t i = 0; i < size_in_bytes; i++) {
		tmp[i] = vector->data[i];
	}

	vector_mem_free(vector->data);

	vector->data = tmp;
	vector->capacity = new_size;

	return true;
}

__attribute__((always_inline)) inline static bool is_callbacks_valid(void)
{
	return ((vector_mem_free != NULL) && (vector_mem_alloc != NULL)) ? true : false;
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
void vector_reg_mem_alloc_cb(void* (*custom_malloc)(size_t sizemem))
{
	assert(custom_malloc);
	vector_mem_alloc = custom_malloc;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
void vector_reg_mem_free_cb(void (*custom_free)(void * ptrmem))
{
	assert(custom_free);
	vector_mem_free = custom_free;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
vector_t* vector_create(size_t nbm, size_t esize)
{
	vector_t* vector = NULL;

	if(!is_callbacks_valid()) {
		return false;
	}

	vector = vector_mem_alloc(sizeof(*vector));
	if (vector == NULL) {
		return NULL;
	}

	vector->size = 0;
	vector->capacity = nbm + RESIZE_FACTOR;
	vector->esize = esize;
	size_t size_in_bytes = vector->capacity * vector->esize;

	vector->data = (uint8_t*) vector_mem_alloc(size_in_bytes);
	if (vector->data == NULL) 
	{
		vector_mem_free((void*)vector);
		return NULL;
	}

	return vector;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
void vector_delete(vector_t **vector)
{
	assert(*vector);

	vector_mem_free((*vector)->data);
	vector_mem_free(*vector);
	*vector = NULL;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_is_empty(const vector_t *vector)
{
	assert(vector);
	return (vector->size == 0) ? true : false;
}

/**
* This function used to check the queue for full.
*
* Public function defined in queue.h
*/
bool vector_is_full(const vector_t *vector)
{
	assert(vector);
	return (vector->size == vector->capacity) ? true : false;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
size_t vector_size(const vector_t *vector)
{
	assert(vector);
	return vector->size;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
size_t vector_capacity(const vector_t *vector)
{
	assert(vector);
	return vector->capacity;
}

/**
* This function return free size of queue.
*
* Public function defined in queue.h
*/
size_t vector_free_space(const vector_t *vector)
{
	assert(vector);
	return vector->capacity - vector->size;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_reset(vector_t *vector)
{
	assert(vector);

	size_t size_in_bytes = vector->size * vector->esize;

	vector->size = 0;

	for(size_t i = 0; i < size_in_bytes; i++) {
		vector->data[i] = 0;
	}

	return true;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_at(const vector_t *vector, void *data, size_t index)
{
	assert(vector);
	assert(data);

	if(index > vector->size ||
		vector_is_empty(vector)) 
	{
		return false;
	}

	uint8_t* pData = (uint8_t*)data;
	size_t size_in_bytes = vector->capacity * vector->esize;

	size_t pos = index * vector->esize;
	for(size_t i = 0; i < vector->esize; i++)
	{
		pData[i] = vector->data[pos + i];
	}

	return true;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_pop_back(vector_t *vector, void *data)
{
	assert(vector);
	assert(data);

	if(vector_is_empty(vector)) 
	{
		return false;
	}

	uint8_t* pData = (uint8_t*)data;
	size_t size_in_bytes = vector->capacity * vector->esize;

	size_t pos = vector->size * vector->esize;
	for(size_t i = 0; i < vector->esize; i++)
	{
		pData[i] = vector->data[pos + i];
		vector->data[pos + i] = 0;
	}

	vector->size--;

	return true;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_extract(vector_t *vector, void *data, size_t index)
{
	assert(vector);
	assert(data);

	if(index > vector->size ||
		vector_is_empty(vector)) 
	{
		return false;
	}

	uint8_t* pData = (uint8_t*)data;
	size_t size_in_bytes = vector->size * vector->esize;

	size_t pos = index * vector->esize;
	for(size_t i = 0; i < vector->esize; i++)
	{
		pData[i] = vector->data[pos + i];
	}

	vector->size--;

	for(size_t i = pos; i < size_in_bytes; i++)
	{
		vector->data[i] = vector->data[pos + i + 1];
	}

	return true;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_pop_front(vector_t *vector, void *data)
{
	assert(vector);
	assert(data);

	if(vector_is_empty(vector)) 
	{
		return false;
	}

	uint8_t* pData = (uint8_t*)data;
	size_t size_in_bytes = vector->capacity * vector->esize;

	size_t pos = 0;
	for(size_t i = 0; i < vector->esize; i++)
	{
		pData[i] = vector->data[pos + i];
		vector->data[pos + i] = 0;
	}

	vector->size--;

	for(size_t i = pos; i < size_in_bytes; i++)
	{
		vector->data[i] = vector->data[pos + i + 1];
	}

	return true;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_erase(vector_t *vector, size_t index)
{
	assert(vector);

	if(index > vector->size ||
		vector_is_empty(vector)) 
	{
		return false;
	}

	size_t size_in_bytes = vector->size * vector->esize;
	size_t pos = index * vector->esize;

	for(size_t i = pos; i < size_in_bytes; i++)
	{
		vector->data[i] = vector->data[pos + i + 1];
	}

	vector->size--;

	return true;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_append(vector_t *vector, void *data)
{
	assert(vector);
	assert(data);

	if(vector_is_full(vector))
	{
		if(vector_resize(vector) != true) {
			return false;
		}
	}

	uint8_t* pData = (uint8_t*)data;
	size_t pos = vector->size * vector->esize;

	for(size_t i = 0; i < vector->esize; i++)
	{
		vector->data[pos + i] = pData[i];
	}
	vector->size++;

	return true;
}

/**
* This function used to register function for alloc memory.
*
* Public function defined in queue.h
*/
bool vector_insert(vector_t *vector, void *data, size_t index)
{
#if 0
	assert(vector);
	assert(data);

	if(index > vector->size)
	{
		return false;
	}

	if(vector_is_full(vector))
	{
		if(vector_resize(vector) != true) {
			return false;
		}
	}




	for(int32_t i = vector->size * vector->esize; i >= (int32_t)index * vector->esize; --i) {
		vector->data[i+1] = vector->data[i];
	}

	vector->data[index] = data;
	vector->size++;

	return true;
#else
	return false;
#endif
}