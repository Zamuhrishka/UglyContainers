/**
 * \file    linked_list.h
 * \author  learnc.info@gmail.com (https://learnc.info/adt/linked_list.html)
 *          Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Linked list data structure and associated operations.
 *
 *  This file provides the interface to create, manage, and destroy a linked list of generic type.
 * \date    2023-01-01
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
struct Private_tag;
typedef struct Private_tag private_t;

/**
 *  \brief Linked list data structure.
 *
 *  This structure represents a generic linked list with operations provided as function pointers.
 */
typedef struct
{
  private_t* private; /**< Private data, internal to the implementation. */

  struct
  {
    bool (*resize)(void* this, size_t new_size);                 /**< Resizes the linked list. */
    bool (*push_front)(void* this, const void* data);            /**< Adds an element to the front of the list. */
    bool (*pop_front)(void* this, void* data);                   /**< Removes an element from the front of the list. */
    bool (*push_back)(void* this, const void* data);             /**< Adds an element to the back of the list. */
    bool (*pop_back)(void* this, void* data);                    /**< Removes an element from the back of the list. */
    bool (*insert)(void* this, const void* data, size_t index);  /**< Inserts an element at the specified index. */
    bool (*extract)(void* this, void* data, size_t index);       /**< Extracts an element from the specified index. */
    bool (*replace)(void* this, const void* data, size_t index); /**< Replaces an element at the specified index. */
    bool (*at)(const void* this, void* data,
               size_t index);                /**< Retrieves an element at the specified index without removing it. */
    bool (*erase)(void* this, size_t index); /**< Removes an element at the specified index. */
    void* (*peek)(void* this,
                  size_t index); /**< Retrieves a pointer to an element at the specified index without removing it. */
    bool (*clear)(void* this);   /**< Clears all elements from the list. */
    size_t (*size)(const void* this); /**< Returns the number of elements in the list. */
  };
} linked_list_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 *  \brief Creates a new linked list with a specified element size.
 *
 *  This function initializes a new linked list with a given element size.
 *  The linked list will be able to store elements of the specified size.
 *
 *  \param[in] esize Size in bytes of each element that the linked list will store.
 *  \return Pointer to the newly created linked list or NULL if the allocation failed.
 */
linked_list_t* linked_list_create(size_t esize);

/**
 *  \brief Frees up the memory associated with the linked list.
 *
 *  This function releases the memory occupied by the linked list and sets the pointer to NULL.
 *
 *  \param[in,out] list Double pointer to the linked list to be deleted.
 */
void linked_list_delete(linked_list_t** list);
