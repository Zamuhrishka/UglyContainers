/**
 * \file vector.h
 * \author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief Vector type data structure and associated function pointers.
 *
 *  This file defines the `vector_t` structure, which represents a vector-based container.
 *  The structure encapsulates private data members and provides function pointers
 *  to operations that can be performed on the vector.
 *  To use a particular implementation, set the function pointers to the appropriate functions.
 * \date 2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "stdbool.h"
#include "stdint.h"
#include <stddef.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
struct Private_tag;
typedef struct Private_tag private_t;

/**
 *  \struct vector_t
 *  \brief Vector container with function pointers for operations.
 *
 *  This structure encapsulates a set of function pointers that represent operations
 *  that can be performed on the vector.
 */
typedef struct
{
  private_t* private;
  struct
  {
    bool (*resize)(void* this, size_t new_size);      /**< Resize the vector to a new size. */
    bool (*push_front)(void* this, const void* data); /**< Add an element to the front of the vector. */
    bool (*pop_front)(void* this, void* data);        /**< Remove and retrieve the front element of the vector. */
    bool (*push_back)(void* this, const void* data);  /**< Add an element to the back of the vector. */
    bool (*pop_back)(void* this, void* data);         /**< Remove and retrieve the back element of the vector. */
    bool (*insert)(void* this, const void* data, size_t index); /**< Insert an element at a specific index. */
    bool (*extract)(void* this, void* data, size_t index); /**< Remove and retrieve an element at a specific index. */
    bool (*replace)(void* this, const void* data, size_t index); /**< Replace an element at a specific index. */
    bool (*at)(const void* this, void* data, size_t index);      /**< Retrieve an element at a specific index. */
    bool (*erase)(void* this, size_t index);                     /**< Remove an element at a specific index. */
    void* (*peek)(void* this, size_t index); /**< Get a pointer to an element at a specific index without removal. */
    bool (*clear)(void* this);               /**< Clear all elements from the vector. */
    size_t (*size)(const void* this);        /**< Get the number of elements in the vector. */
  };
} vector_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 *  \brief Creates a new vector with a specified element size.
 *
 *  This function initializes a new vector with a given element size.
 *  The vector will be able to store elements of the specified size.
 *
 *  \param[in] esize Size in bytes of each element that the vector will store.
 *  \return Pointer to the newly created vector or NULL if the allocation failed.
 */
vector_t* vector_create(size_t esize);

/**
 *  \brief Frees up the memory associated with the vector.
 *
 *  This function releases the memory occupied by the vector and sets the pointer to NULL.
 *
 *  \param[in,out] vector Double pointer to the vector to be deleted.
 */
void vector_delete(vector_t** vector);
