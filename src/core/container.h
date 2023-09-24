/**
 * \file    container.h
 * \author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Universal data storage container.
 *
 * This file contains function prototypes for working with a universal container.
 * The container can be implemented based on a linked list or a vector.
 * The provided functions allow for basic operations on the container,
 * such as adding, removing, extracting, and replacing elements.
 *
 * For correct operation with the container, before using the container functions,
 * it's necessary to initialize memory allocation and deallocation functions using
 * the `container_alloc_init` function.
 *
 * \date  2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "interface/allocator_if.h"

#include <stdbool.h>
#include <stddef.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
struct Container_tag;
typedef struct Container_tag container_t;

/**
 *  \brief Enumerates the types of containers available.
 */
typedef enum ContainerType_tag
{
  CONTAINER_LINKED_LIST_BASED = 0, /**< Specifies a container based on a linked list. */
  CONTAINER_VECTOR_BASED = 1,      /**< Specifies a container based on a vector (dynamic array). */
} container_type_e;

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes the container allocator with custom memory functions.
 *
 * \param alloc_cb Callback function for memory allocation.
 * \param free_cb Callback function for memory deallocation.
 */
void container_alloc_init(allocate_fn_t alloc_cb, free_fn_t free_cb);

/**
 * \brief Creates a new container of a specified type.
 *
 * \param esize Size in bytes of the single element that this container will store.
 * \param type Type of the container to be created.
 * \return Pointer to the newly created container or NULL if creation failed.
 */
container_t *container_create(size_t esize, container_type_e type);

/**
 * \brief Frees up the memory associated with the container.
 *
 * \param container Double pointer to the container to be deleted.
 */
void container_delete(container_t **container);

/**
 * \brief Resizes the container to a new size.
 *
 * \param container Pointer to the container.
 * \param new_size The new size for the container.
 * \return true if resizing was successful, false otherwise.
 */
bool container_resize(container_t *container, size_t new_size);

/**
 * \brief Pushes an element to the front of the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to the data to be pushed.
 * \return true if the operation was successful, false otherwise.
 */
bool container_push_front(container_t *container, const void *data);

/**
 * \brief Pops an element from the front of the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to store the popped data.
 * \return true if the operation was successful, false otherwise.
 */
bool container_pop_front(container_t *container, void *data);

/**
 * \brief Pushes an element to the back of the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to the data to be pushed.
 * \return true if the operation was successful, false otherwise.
 */
bool container_push_back(container_t *container, const void *data);

/**
 * \brief Pops an element from the back of the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to store the popped data.
 * \return true if the operation was successful, false otherwise.
 */
bool container_pop_back(container_t *container, void *data);

/**
 * \brief Inserts an element at a specified index in the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to the data to be inserted.
 * \param index The index at which the data should be inserted.
 * \return true if the operation was successful, false otherwise.
 */
bool container_insert(container_t *container, const void *data, size_t index);

/**
 * \brief Extracts an element from a specified index in the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to store the extracted data.
 * \param index The index from which the data should be extracted.
 * \return true if the operation was successful, false otherwise.
 */
bool container_extract(container_t *container, void *data, size_t index);

/**
 * \brief Replaces an element at a specified index in the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to the data to replace the current one.
 * \param index The index at which the data should be replaced.
 * \return true if the operation was successful, false otherwise.
 */
bool container_replace(container_t *container, const void *data, size_t index);

/**
 * \brief Retrieves an element from a specified index in the container.
 *
 * \param container Pointer to the container.
 * \param data Pointer to store the retrieved data.
 * \param index The index from which the data should be retrieved.
 * \return true if the operation was successful, false otherwise.
 */
bool container_at(const container_t *container, void *data, size_t index);

/**
 * \brief Erases an element at a specified index in the container.
 *
 * \param container Pointer to the container.
 * \param index The index at which the element should be erased.
 * \return true if the operation was successful, false otherwise.
 */
bool container_erase(container_t *container, size_t index);

/**
 * \brief Peeks at an element at a specified index in the container without removing it.
 *
 * \param container Pointer to the container.
 * \param index The index from which the data should be peeked.
 * \return Pointer to the peeked data or NULL.
 */
void *container_peek(const container_t *container, size_t index);

/**
 * \brief Clears all the elements from the container.
 *
 * \param container Pointer to the container.
 * \return true if the operation was successful, false otherwise.
 */
size_t container_clear(const container_t *container);

/**
 * \brief Returns the number of elements in the container.
 *
 * \param container Pointer to the container.
 * \return Number of elements in the container.
 */
size_t container_size(const container_t *container);

/**
 * \brief Returns the size of single element (in bytes).
 *
 * \param container Pointer to the container.
 * \return Size of single element.
 */
size_t container_esize(const container_t *container);
