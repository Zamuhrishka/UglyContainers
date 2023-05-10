/**
 * @file bt.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-02-20
 */

//_____ I N C L U D E S _______________________________________________________
#include "bt.h"

#include <assert.h>
#include "allocator_if.h"
#include "contants.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Node
{
    void* data;
    struct Node *left;
    struct Node *right;
};

struct bt
{
    struct Node* root;
    btcmp_fn_t compare;
    size_t esize;
    // size_t size;
};

//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static struct Node* max(struct Node* root);

/**
 * \brief Create new tree node
 *
 * \param[in] data pointer to data which need to be store in node
 * \param[in] esize size (in  bytes) of data
 * \return struct Node*
 */
static struct Node* node_new(void* data, size_t esize)
{
    assert(data && "Invalid argument: data");

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
 * \brief Free selected tree node
 *
 * \param[in] node double pointer on node which need to be deleted
 */
static void node_free(struct Node** node)
{
    assert(*node && "Invalid argument: data");

    allocate_fn_t mem_free = get_free();

    mem_free(*node);
    *node = NULL;
}

/**
 * \brief Insert new node into tree
 *
 * \param[in] root
 * \param[in] data
 * \param[in] esize
 * \param[in] cmp_cb
 */
#if 0
static void insert(struct Node* root, void* data, size_t esize, btcmp_fn_t cmp_cb)
{
    assert(root && "Invalid input pointer\n");
    assert(cmp_cb && "Invalid input pointer\n");

    if (cmp_cb(data, root->data) < 0)
    {
        if (root->left == NULL) root->left = node_new(data, esize);
        else insert_node(&(*root)->left, data, esize, cmp_cb);
    }
    else
    {
        if (root->right == NULL) root->right = node_new(data, esize);
        else insert_node(&(*root)->right, data, esize, cmp_cb);
    }
}
#else
static void insert(struct Node* root, struct Node* node, btcmp_fn_t compare_cb)
{
    assert(root && "Invalid argument: root");
    assert(node && "Invalid argument: node");
    assert(compare_cb && "Invalid argument: compare_cb");

    if (compare_cb(node->data, root->data) < 0)
    {
        if (root->left == NULL) root->left = node;
        else insert(root->left, node, compare_cb);
    }
    else
    {
        if (root->right == NULL) root->right = node;
        else insert(root->right, node, compare_cb);
    }
}
#endif
/**
 * \brief Delete selected node from tree
 *
 * \param[] root
 * \param[] data
 * \param[] cmp_cb
 * \return struct Node*
 */
#if 0
static struct Node* delete(struct Node** root, void* data, btcmp_fn_t compare_cb)
{
    assert(data && "Invalid input pointer\n");
    assert(cmp_cb && "Invalid input pointer\n");

    if (*root == NULL) return NULL;
    else if (cmp_cb(data, node->data) < 0) *root->left = delete(&root->left, data, cmp_cb);
    else if (cmp_cb(data, node->data) > 0) *root->right = delete(&root->right, data, cmp_cb);
    else
    {
        if (*root->left == NULL || *root->right == NULL)
        {
            root = (*root->left == NULL) ? &root->right : &root->left;
        }
        else
        {
            struct Node* max_in_left = max_node(root->left);
            *root->data = max_in_left->data;
            *root->right = delete(&root->right, data, cmp_cb);
        }
    }

    return root;
}
#else
// static struct Node* remove(struct Node* root, struct Node* node, btcmp_fn_t compare_cb)
static struct Node* remove(struct Node** p_root, struct Node* node, btcmp_fn_t compare_cb)
{
    struct Node* root = *p_root;

    if (root == NULL)
    {
        return NULL;
    }

    cmp_t result = compare_cb(node->data, root->data);

    if (result == LE) root->left = remove(&root->left, node, compare_cb);
    else if (result == GT) root->right = remove(&root->right, node, compare_cb);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            struct Node* tmp = root;
            *p_root = (root->left == NULL) ? root->right : root->left;
            free(tmp);
        }
        else
        {
            struct Node* max_in_left = max(root->left);

            // FIX: Execute copy function
            root->data = max_in_left->data;

            // root->right = remove(&root->left, max_in_left, compare_cb);
            remove(&root->left, max_in_left, compare_cb);
        }
    }

    return *p_root;



    // if (root == NULL) return NULL;
    // else if (compare_cb((root)->data, node->data) < 0) (root)->left = remove(&root->left, node, compare_cb);
    // else if (compare_cb((root)->data, node->data) > 0) (root)->right = remove(&root->right, node, compare_cb);
    // else
    // {
    //     if ((root->left) == NULL || (root)->right == NULL)
    //     {
    //         root = (root->left == NULL) ? root->right : root->left;
    //     }
    //     else
    //     {
    //         struct Node* max_in_left = max((root)->left);
    //         (root)->data = max_in_left->data;
    //         (root)->right = remove(root->right, node, compare_cb);
    //     }
    // }

    // return root;

    // return NULL;
}
#endif

/**
 * \brief Find node with selected data
 *
 * \param[] node
 * \param[] data
 * \param[] cmp_cb
 * \return struct Node*
 */
#if 0
static struct Node* search(struct Node* node, void* data, btcmp_fn_t cmp_cb)
{
    assert(cmp_cb && "Invalid input pointer\n");

    if (node == NULL) return NULL;
    if (cmp_cb(data, node->data) == 0) return node;

    return (cmp_cb(data, node->data) < 0) ?
            search_node(node->left, data, cmp_cb) :
            search_node(node->right, data, cmp_cb);
}
#else
static struct Node* search(struct Node* root, struct Node* node, btcmp_fn_t compare_cb)
{
    // assert(root && "Invalid argument: root");
    // assert(node && "Invalid argument: node");
    // assert(compare_cb && "Invalid argument: compare_cb");

    struct Node* _node = node;

    if (root == NULL) return NULL;

    int result = compare_cb(_node->data, root->data);

    if (result == 0) return root;

    return (result < 0) ?
            search(root->left, _node, compare_cb) :
            search(root->right, _node, compare_cb);

    // if (compare_cb(node->data, root->data) == 0) return root;

    // return (compare_cb(node->data, root->data) < 0) ?
    //         search(root->left, node, compare_cb) :
    //         search(root->right, node, compare_cb);
}
#endif

/**
 * \brief Return node with min value
 *
 * \param[] root
 * \return struct Node*
 */
static struct Node* min(struct Node* root)
{
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return min(root->left);
}

/**
 * \brief Return node with max value
 *
 * \param[] root
 * \return struct Node*
 */
static struct Node* max(struct Node* root)
{
    if (root == NULL) return NULL;
    if (root->right == NULL) return root;
    return max(root->right);
}

/**
 * \brief Traversal of tree in pre order and call the callback function for each node
 *
 * \note Данный обход может использоваться при копировании дерева в памяти.
 *
 * \param[] node
 * \param[] callback
 */
void node_pre_order_traversal(struct Node *node, void (*callback)(void* data))
{
    if (node != NULL)
    {
        callback(node->data);
        node_pre_order_traversal(node->left, callback);
        node_pre_order_traversal(node->right, callback);
    }
}

/**
 * \brief Traversal of tree in post order and call the callback function for each node
 *
 * \note Данный обход позволяет безопасно удалить все узлы дерева для языков, которые с ручным управлением памятью.
 *       Потому что при таком подходе всегда удаляется узел который сам ни на кого не ссылается.
 *
 * \param[] node
 * \param[] callback
 */
void node_post_order_traversal(struct Node *node, void (*callback)(void* data))
{
    if (node != NULL)
    {
        node_post_order_traversal(node->left, callback);
        node_post_order_traversal(node->right, callback);
        callback(node->data);
    }
}

/**
 * \brief Traversal of tree in symmetric order and call the callback function for each node
 *
 * \note Данный обход позволяет выводит дерево в порядке возрастание его элементов.
 *
 * \param[] node
 * \param[] callback
 */
void node_inorder_order_traversal(struct Node *node, void (*callback)(void* data))
{
    if (node != NULL)
    {
        node_inorder_order_traversal(node->left, callback);
        callback(node->data);
        node_inorder_order_traversal(node->right, callback);
    }
}

//_____ P U B L I C  F U N C T I O N S_________________________________________
bt_t* bt_create(size_t esize, btcmp_fn_t compare_cb)
{
    assert(compare_cb && "Compare callback is invalid!");
    assert(esize != 0 && "esize is invalid!");

    allocate_fn_t mem_allocate = get_allocator();

    bt_t* bt = (bt_t*)mem_allocate(sizeof(bt_t));
    if (NULL == bt)
    {
        return NULL;
    }

    bt->esize = esize;
    bt->compare = compare_cb;
    bt->root = NULL;
    // bt->size = 0;
}

void bt_delete(bt_t* bt)
{

}

bool bt_insert(bt_t* bt, void* data)
{
    assert(bt && "Wrong arg: bt");
    assert(data && "Wrong arg: data");

    struct Node* node = node_new(data, bt->esize);
    if(NULL == node)
    {
        return false;
    }

    memcpy(node->data, data, bt->esize);

    if (NULL == bt->root)
    {
        bt->root = node;
    }
    else
    {
        insert(bt->root, node, bt->compare);
    }

    //BUG: free function bring memory error
    // node_free(&node);

    return true;
}

bool bt_remove(bt_t* bt, void* data)
{
    assert(bt && "Wrong arg: bt");
    assert(data && "Wrong arg: data");

    if(NULL == bt->root)
    {
        return false;
    }

    struct Node* node = node_new(data, bt->esize);
    if(NULL == node)
    {
        return false;
    }

    remove(&bt->root, node, bt->compare);

    //BUG: free function bring memory error
    // node_free(&node);

    return true;
}


void* bt_min(const bt_t* bt)
{
    assert(bt && "Wrong arg: bt");

    struct Node* min_node = min(bt->root);
    if(NULL == min_node)
    {
        return NULL;
    }

    return min_node->data;
}

//Return max value
void* bt_max(const bt_t* bt)
{
    assert(bt && "Wrong arg: bt");

    struct Node* max_node = max(bt->root);
    if(NULL == max_node)
    {
        return NULL;
    }

    return max_node->data;
}

bool bt_search(bt_t* bt, void* data)
{
    assert(bt && "Wrong arg: bt");
    assert(bt && "Wrong arg: data");

    struct Node* node = node_new(data, bt->esize);
    if(NULL == node)
    {
        return false;
    }

    return search(bt->root, node, bt->compare);

    // node_free(struct Node** node)
}

void bt_pre_order_traversal(const bt_t* bt, void (*callback)(void* data))
{
    assert(bt && "Wrong arg: bt");

    node_pre_order_traversal(bt->root, callback);
}

void bt_post_order_traversal(const bt_t* bt, void (*callback)(void* data))
{
    assert(bt && "Wrong arg: bt");

    node_post_order_traversal(bt->root, callback);
}

void bt_in_order_traversal(const bt_t* bt, void (*callback)(void* data))
{
    assert(bt && "Wrong arg: bt");

    node_inorder_order_traversal(bt->root, callback);
}
