/**
 * @file bst.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-02-20
 */

//_____ I N C L U D E S _______________________________________________________
#include "bst.h"

#include <assert.h>
#include "allocator_if.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
/**
 * \brief Node of binary search tree
 */
struct Node
{
    void* data;
    struct Node *left;
    struct Node *right;
};

/**
 * \brief Binary Search Tree
 */
struct bst
{
    struct Node* root;
    bst_compare_cb compare;
    size_t esize;
};

//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static struct Node* node_max(struct Node* root);
static void node_free(struct Node** node);

static void nodes_free_traversal(struct Node *root)
{
    if (root != NULL)
    {
        nodes_free_traversal(root->left);
        nodes_free_traversal(root->right);
        node_free(&root);
    }
}

/**
 * \brief Create new tree node
 *
 * \param[in] data pointer to data which need to be store in node
 * \param[in] esize size (in  bytes) of stored data
 * \return struct Node*
 */
static struct Node* node_new(void* data, size_t esize)
{
    assert(data && "Invalid argument: data");
    assert(esize != 0 && "Invalid argument: esize can`t be 0");

    allocate_fn_t mem_allocate = get_allocator();

    struct Node* node = (struct Node*)mem_allocate(sizeof(struct Node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = (void*)mem_allocate(esize);
    if(NULL == node->data)
    {
        return NULL;
    }

    memcpy(node->data, data, esize);
    node->left = NULL;
    node->right = NULL;

    return node;
}

/**
 * \brief Free tree node
 *
 * \param[in] node double pointer on node which need to be deleted
 */
static void node_free(struct Node** node)
{
    // assert(*node && "Invalid argument: *node");
    // assert(node && "Invalid argument: node");

    allocate_fn_t mem_free = get_free();
    mem_free((*node)->data);
    mem_free(*node);
    node = NULL;
}

/**
 * \brief Insert new node into tree
 *
 * \param[in] root root node
 * \param[in] node node which need to be inserted
 * \param[in] cmp_cb callback function for data compare
 */
static void node_insert(struct Node* root, struct Node* node, bst_compare_cb compare_cb)
{
    assert(root && "Invalid argument: root");
    assert(node && "Invalid argument: node");
    assert(compare_cb && "Invalid argument: compare_cb");

    cmp_t result = compare_cb(node->data, root->data);

    if (result == LE)
    {
        if (root->left == NULL) root->left = node;
        else node_insert(root->left, node, compare_cb);
    }
    else if (result == GT)
    {
        if (root->right == NULL) root->right = node;
        else node_insert(root->right, node, compare_cb);
    }
}

/**
 * \brief Delete node from tree
 *
 * \param[in] root root node
 * \param[in] node node which need to be inserted
 * \param[in] cmp_cb callback function for data compare
 *
 * \return none
 */
static void node_remove(struct Node** p_root, const struct Node* node, bst_compare_cb compare_cb)
{
    assert(node && "Invalid argument: node");
    assert(compare_cb && "Invalid argument: compare_cb");

    struct Node* root = *p_root;

    if (root == NULL)
    {
        return NULL;
    }

    cmp_t result = compare_cb(node->data, root->data);

    if (result == LE) node_remove(&root->left, node, compare_cb);
    else if (result == GT) node_remove(&root->right, node, compare_cb);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            struct Node* tmp = root;
            *p_root = (root->left == NULL) ? root->right : root->left;
            node_free(&tmp);
        }
        else
        {
            struct Node* max_in_left = node_max(root->left);
            // FIX: Execute copy function
            root->data = max_in_left->data;
            node_remove(&root->left, max_in_left, compare_cb);
        }
    }
}

/**
 * \brief Find node with selected data in tree
 *
 * \param[in] root root node
 * \param[in] node node which need to be inserted
 * \param[in] compare_cb callback function for data compare
 *
 * \return found node
 */
static struct Node* node_search(struct Node* root, struct Node* node, bst_compare_cb compare_cb)
{
    assert(node && "Invalid argument: node");
    assert(compare_cb && "Invalid argument: compare_cb");

    if (root == NULL) return NULL;

    cmp_t result = compare_cb(node->data, root->data);

    if (result == EQ) return root;

    return (result == LE) ?
            node_search(root->left, node, compare_cb) :
            node_search(root->right, node, compare_cb);
}

/**
 * \brief Return node with min value
 *
 * \param[in] root node
 *
 * \return min node
 */
static struct Node* node_min(struct Node* root)
{
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;

    return node_min(root->left);
}

/**
 * \brief Return node with max value
 *
 * \param[in] root node
 *
 * \return max node
 */
static struct Node* node_max(struct Node* root)
{
    if (root == NULL) return NULL;
    if (root->right == NULL) return root;

    return node_max(root->right);
}

/**
 * \brief Traversal of tree in pre order and call the callback function for each node
 *
 * \note This traversal can be used when copying the tree to memory.
 *
 * \param[in] root root node
 * \param[in] callback callback function for data compare
 */
void node_pre_order_traversal(struct Node *root, bst_traversal_cb callback)
{
    if (root != NULL)
    {
        callback(root->data);
        node_pre_order_traversal(root->left, callback);
        node_pre_order_traversal(root->right, callback);
    }
}

/**
 * \brief Traversal of tree in post order and call the callback function for each node
 *
 * \note This traversal allows you to safely delete all tree nodes. Because with this approach,
 *       a node that does not refer to anyone is always deleted.
 *
 * \param[in] root root node
 * \param[in] callback callback function for data compare
 */
void node_post_order_traversal(struct Node *root, bst_traversal_cb callback)
{
    if (root != NULL)
    {
        node_post_order_traversal(root->left, callback);
        node_post_order_traversal(root->right, callback);
        callback(root->data);
    }
}

/**
 * \brief Traversal of tree in symmetric order and call the callback function for each node
 *
 * \note This traversal allows you to output the tree in ascending order of its elements
 *
 * \param[in] root root node
 * \param[in] callback callback function for data compare
 */
void node_in_order_order_traversal(struct Node *root, bst_traversal_cb callback)
{
    if (root != NULL)
    {
        node_in_order_order_traversal(root->left, callback);
        callback(root->data);
        node_in_order_order_traversal(root->right, callback);
    }
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
* Create binary search tree
*
* Public function defined in bst.h
*/
bst_t* bst_create(size_t esize, bst_compare_cb compare_cb)
{
    assert(compare_cb && "Compare callback is invalid!");
    assert(esize != 0 && "esize is invalid!");

    allocate_fn_t mem_allocate = get_allocator();

    bst_t* bst = (bst_t*)mem_allocate(sizeof(bst_t));
    if (NULL == bst)
    {
        return NULL;
    }

    bst->esize = esize;
    bst->compare = compare_cb;
    bst->root = NULL;
}

/**
* Delete binary search tree
*
* Public function defined in bst.h
*/
void bst_delete(bst_t** bst)
{
    assert(bst && "Wrong arg: bst");

    if (*bst != NULL)
    {
        nodes_free_traversal((*bst)->root);
    }

    allocate_fn_t mem_free = get_free();
    mem_free(*bst);
    bst = NULL;
}

/**
* Insert new data into binary search tree
*
* Public function defined in bst.h
*/
bool bst_insert(bst_t* bst, const void* data)
{
    assert(bst && "Wrong arg: bst");
    assert(data && "Wrong arg: data");

    struct Node* node = node_new(data, bst->esize);
    if(NULL == node)
    {
        return false;
    }

    memcpy(node->data, data, bst->esize);

    if (NULL == bst->root)
    {
        bst->root = node;
    }
    else
    {
        node_insert(bst->root, node, bst->compare);
    }

    return true;
}

/**
* Remove selected data from binary search tree
*
* Public function defined in bst.h
*/
bool bst_remove(bst_t* bst, void* data)
{
    assert(bst && "Wrong arg: bst");
    assert(data && "Wrong arg: data");

    if(NULL == bst->root)
    {
        return false;
    }

    struct Node* node = node_new(data, bst->esize);
    if(NULL == node)
    {
        return false;
    }

    node_remove(&bst->root, node, bst->compare);

    node_free(&node);

    return true;
}

/**
* Return min value
*
* Public function defined in bst.h
*/
void* bst_min(const bst_t* bst)
{
    assert(bst && "Wrong arg: bst");

    struct Node* min_node = node_min(bst->root);
    if(NULL == min_node)
    {
        return NULL;
    }

    void* min = min_node->data;

    node_free(&min_node);

    return min;
}

/**
* Return max value
*
* Public function defined in bst.h
*/
void* bst_max(const bst_t* bst)
{
    assert(bst && "Wrong arg: bst");

    struct Node* max_node = node_max(bst->root);
    if(NULL == max_node)
    {
        return NULL;
    }

    void* max = max_node->data;

    node_free(&max_node);

    return max;
}

/**
* Find selected data in tree
*
* Public function defined in bst.h
*/
bool bst_search(bst_t* bst, void* data)
{
    assert(bst && "Wrong arg: bst");
    assert(bst && "Wrong arg: data");

    struct Node* node = node_new(data, bst->esize);
    if(NULL == node)
    {
        return false;
    }

    struct Node* s_node = node_search(bst->root, node, bst->compare);

    if (NULL == s_node)
    {
        return false;
    }

    // *data = s_node->data;

    node_free(&node);

    return true;
}

/**
* Traversal of tree in pre order and call the callback function for each node
*
* Public function defined in bst.h
*/
void bst_pre_order_traversal(const bst_t* bst, bst_traversal_cb callback)
{
    assert(bst && "Wrong arg: bst");

    node_pre_order_traversal(bst->root, callback);
}

/**
* Traversal of tree in post order and call the callback function for each node
*
* Public function defined in bst.h
*/
void bst_post_order_traversal(const bst_t* bst, bst_traversal_cb callback)
{
    assert(bst && "Wrong arg: bst");

    node_post_order_traversal(bst->root, callback);
}

/**
* Traversal of tree in symmetric order and call the callback function for each node
*
* Public function defined in bst.h
*/
void bst_in_order_traversal(const bst_t* bst, bst_traversal_cb callback)
{
    assert(bst && "Wrong arg: bst");

    node_in_order_order_traversal(bst->root, callback);
}
