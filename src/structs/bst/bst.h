/**
 * @file bst.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-02-20
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdint.h>
#include <stdbool.h>
#include "contants.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct bst;
typedef struct bst bst_t;

typedef cmp_t (*bst_compare_cb)(void*, void*);
typedef void (*bst_traversal_cb)(void*);
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Create binary search tree
 *
 * \param[in] esize size in bytes of data which will be store in tree
 * \param[in] compare_cb callback function for compare 2 data
 *
 * \return pointer to created tree or NULL
 */
bst_t* bst_create(size_t esize, bst_compare_cb compare_cb);

/**
 * \brief Delete binary search tree
 *
 * \param[in] bst double pointer to binary search tree
 */
void bst_delete(bst_t** bst);

/**
 * \brief Insert new data into binary search tree
 *
 * \param[in] bst tree
 * \param[in] data new data
 *
 * \return true
 * \return false
 */
bool bst_insert(bst_t* bst, const void* data);

/**
 * \brief Remove selected data from binary search tree
 *
 * \param[in] bst tree
 * \param[in] data removed data
 *
 * \return true
 * \return false
 */
bool bst_remove(bst_t* bst, void* data);

/**
 * \brief Return min value
 *
 * \param[in] bst tree
 *
 * \return pointer to min value
 */
void* bst_min(const bst_t* bst);

/**
 * \brief Return max value
 *
 * \param[in] bst tree
 *
 * \return pointer to max value
 */
void* bst_max(const bst_t* bst);

/**
 * \brief Find selected data in tree
 *
 * \param[in] bst tree
 * \param[in] node data which need to be found
 *
 * \return true
 * \return false
 */
bool bst_search(bst_t* bst, void* data);

/**
 * \brief Traversal of tree in pre order and call the callback function for each node
 *
 * \note This traversal can be used when copying the tree to memory.
 *
 * \param[in] bst tree
 * \param[in] callback callback function for data compare
 */
void bst_pre_order_traversal(const bst_t* bst, bst_traversal_cb callback);

/**
 * \brief Traversal of tree in post order and call the callback function for each node
 *
 * \note This traversal allows you to safely delete all tree nodes. Because with this approach,
 *       a node that does not refer to anyone is always deleted.
 *
 * \param[in] bst tree
 * \param[in] callback callback function for data compare
 */
void bst_post_order_traversal(const bst_t* bst, bst_traversal_cb callback);

/**
 * \brief Traversal of tree in symmetric order and call the callback function for each node
 *
 * \note This traversal allows you to output the tree in ascending order of its elements
 *
 * \param[in] bst tree
 * \param[in] callback callback function for data compare
 */
void bst_in_order_traversal(const bst_t* bst, bst_traversal_cb callback);
