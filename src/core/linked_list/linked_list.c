/**
 * @file
 * @author learnc.info@gmail.com (https://learnc.info/adt/linked_list.html)
 *         Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief Double-linked list
 * @date 2023-01-01
 */

//_____ I N C L U D E S _______________________________________________________
#include "linked_list.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
typedef struct _Node_tag
{
    void* data;
    struct _Node_tag* next;
    struct _Node_tag* prev;
} node_t;

struct Private_tag
{
    size_t esize;
    size_t size;
    node_t* head;
    node_t* tail;
};

//_____ M A C R O S ___________________________________________________________
#define IS_NODE_LAST(node) (NULL == node->next)
#define IS_NODE_FIRST(node) (NULL == node->prev)
#define IS_NODE_NOT_LAST(node) (NULL != node->next)
#define IS_NODE_NOT_FIRST(node) (NULL != node->prev)
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static inline bool is_empty(linked_list_t* linked_list)
{
    return (0 == linked_list->private->size);
}

static inline node_t* node_allocate(size_t data_size)
{
    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    node_t* tmp = (node_t*)mem_allocate(sizeof(node_t));
    if (NULL == tmp)
    {
        return NULL;
    }

    tmp->data = mem_allocate(data_size);
    if (NULL == tmp->data)
    {
        free_fn_t mem_free = get_free();
        assert(mem_free);
        mem_free(tmp);
        return NULL;
    }

    return tmp;
}

static inline void node_free(node_t* node)
{
    assert(node);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    mem_free(node->data);
    mem_free(node);
}

static inline void list_free(linked_list_t* linked_list)
{
    assert(linked_list);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    mem_free(linked_list);
}

static inline linked_list_t* list_allocate(void)
{
    if (!is_allocator_valid())
    {
        return NULL;
    }

    allocate_fn_t mem_allocate = get_allocator();
    free_fn_t mem_free = get_free();

    // TODO: Add some align checking?
    linked_list_t* linked_list = (linked_list_t*)mem_allocate(sizeof(linked_list_t));
    if (NULL == linked_list)
    {
        return NULL;
    }

    linked_list->private = (private_t*)mem_allocate(sizeof(private_t));
    if (NULL == linked_list->private)
    {
        mem_free(linked_list);
        return NULL;
    }

    return linked_list;
}

static inline node_t* get_nth(node_t* head, size_t index)
{
    size_t counter = 0;
    while (counter < index && head)
    {
        head = head->next;
        counter++;
    }

    return head;
}

static bool push_front_cb(void* list, const void* data)
{
    assert(list);
    assert(data);

    linked_list_t* linked_list = (linked_list_t*)list;

    // TODO: Add some align checking?
    node_t* tmp = node_allocate(linked_list->private->esize);
    if (NULL == tmp)
    {
        return false;
    }

    // Fill fields of new node
    memcpy(tmp->data, data, linked_list->private->esize);
    tmp->next = linked_list->private->head;
    tmp->prev = NULL;

    // If list wasn`t empty then put prev pointer of first node to the new node
    if (linked_list->private->head)
    {
        linked_list->private->head->prev = tmp;
    }

    // Put HEAD pointer to new node
    linked_list->private->head = tmp;

    // If list was empty then put TAIL pointer to new node
    if (linked_list->private->tail == NULL)
    {
        linked_list->private->tail = tmp;
    }

    linked_list->private->size++;

    return true;
}

static bool pop_front_cb(void* list, void* data)
{
    assert(list);
    assert(data);

    linked_list_t* linked_list = (linked_list_t*)list;

    if (is_empty(linked_list))
    {
        return false;
    }

    // Save HEAD pointer
    node_t* prev_head = linked_list->private->head;

    memcpy(data, linked_list->private->head->data, linked_list->private->esize);

    // Move HEAD pointer to the second node
    linked_list->private->head = linked_list->private->head->next;

    // If list wasn`t empty then put prev pointer of first node to NULL
    if (linked_list->private->head)
    {
        linked_list->private->head->prev = NULL;
    }

    // If list became empty then put TAIL to NULL
    if (prev_head == linked_list->private->tail)
    {
        linked_list->private->tail = NULL;
    }

    node_free(prev_head);

    linked_list->private->size--;

    return true;
}

static bool push_back_cb(void* list, const void* data)
{
    assert(list);
    assert(data);

    linked_list_t* linked_list = (linked_list_t*)list;

    // TODO: Add some align checking?
    node_t* tmp = node_allocate(linked_list->private->esize);
    if (NULL == tmp)
    {
        return false;
    }

    // Fill fields of new node
    memcpy(tmp->data, data, linked_list->private->esize);
    tmp->next = NULL;
    tmp->prev = linked_list->private->tail;

    // If list wasn`t empty then put next pointer of last node to the new node
    if (linked_list->private->tail)
    {
        linked_list->private->tail->next = tmp;
    }

    // Put TAIL pointer to new node
    linked_list->private->tail = tmp;

    // If list was empty then put HEAD pointer to new node
    if (linked_list->private->head == NULL)
    {
        linked_list->private->head = tmp;
    }

    linked_list->private->size++;

    return true;
}

static bool pop_back_cb(void* list, void* data)
{
    assert(list);
    assert(data);

    linked_list_t* linked_list = (linked_list_t*)list;

    if (is_empty(linked_list))
    {
        return false;
    }

    // Save TAIL pointer
    node_t* prev_tail = linked_list->private->tail;

    memcpy(data, prev_tail->data, linked_list->private->esize);

    // Move TAIL pointer to the penultimate node
    linked_list->private->tail = linked_list->private->tail->prev;

    // If list wasn`t empty then put next pointer of last node to NULL
    if (linked_list->private->tail)
    {
        linked_list->private->tail->next = NULL;
    }

    // If list became empty then put HEAD to NULL
    if (prev_tail == linked_list->private->head)
    {
        linked_list->private->head = NULL;
    }

    node_free(prev_tail);

    linked_list->private->size--;

    return true;
}

static bool insert_cb(void* list, const void* data, size_t index)
{
    assert(list);
    assert(data);

    linked_list_t* linked_list = (linked_list_t*)list;

    if (index > linked_list->private->size)
    {
        return false;
    }

    if (is_empty(linked_list) || index == 0)
    {
        linked_list->push_front(linked_list, data);
    }
    else
    {
        node_t* tmp = node_allocate(linked_list->private->esize);
        if (NULL == tmp)
        {
            return false;
        }

        node_t* elm = get_nth(linked_list->private->head, index-1);

        // Fill fields of new node
        memcpy(tmp->data, data, linked_list->private->esize);
        tmp->prev = elm;
        tmp->next = elm->next;

        // If elm is not last node then put PREV pointer for next node to new node
        if (elm->next)
        {
            elm->next->prev = tmp;
        }

        // Put NEXT pointer for previous node to new node
        elm->next = tmp;

        // If now new node is first then change HEAD
        if (NULL == elm->prev)
        {
            linked_list->private->head = elm;
        }

        // If now new node is last then change TAIL
        if (NULL == elm->next)
        {
            linked_list->private->tail = elm;
        }

        linked_list->private->size++;
    } 

    return true;
}

static bool extract_cb(void* list, void* data, size_t index)
{
    assert(list);
    assert(data);

    linked_list_t* linked_list = (linked_list_t*)list;

    if (index > linked_list->private->size)
    {
        return false;
    }

   
    return true;
}

static bool at_cb(const void* list, void* data, size_t index)
{
    assert(list);
    assert(data);

    linked_list_t* linked_list = (linked_list_t*)list;

    if (index > linked_list->private->size)
    {
        return false;
    }

    node_t* elm = get_nth(linked_list->private->head, index);
    if (NULL == elm)
    {
        return false;
    }

    memcpy(data, elm->data, linked_list->private->esize);

    return true;
}

static bool erase_cb(void* list, size_t index)
{
    assert(list);

    linked_list_t* linked_list = (linked_list_t*)list;

    if (is_empty(linked_list) || index > linked_list->private->size)
    {
        return false;
    }

    node_t* elm = get_nth(linked_list->private->head, index);
    if (NULL == elm)
    {
        return false;
    }

    //If erase not first node then move NEXT for previous node
    if (IS_NODE_NOT_FIRST(elm))
    {
        elm->prev->next = elm->next;
    }

    //If erase not last node then move PREV for previous node
    if (IS_NODE_NOT_LAST(elm))
    {
        elm->next->prev = elm->prev;
    }

    //If erase first node then move HEAD
    if (IS_NODE_FIRST(elm))
    {
        linked_list->private->head = elm->next;
    }

    //If erase last node then move TAIL
    if (IS_NODE_LAST(elm))
    {
        linked_list->private->tail = elm->prev;
    }

    node_free(elm);

    linked_list->private->size--;

    return true;
}

static bool clear_cb(const void* list)
{
    assert(list);

    linked_list_t* linked_list = (linked_list_t*)list;

    node_t* tmp = linked_list->private->head;

    while (tmp) {
        node_t* next = tmp->next;
        node_free(tmp);
        tmp = next;
    }

    linked_list->private->head = linked_list->private->tail = NULL;
    linked_list->private->size = 0;
    linked_list->private->esize = linked_list->private->esize;
}


static size_t size_cb(const void* list)
{
    assert(list);

    return ((linked_list_t*)list)->private->size;
}

//_____ P U B L I C  F U N C T I O N S_________________________________________
linked_list_t* linked_list_create(size_t esize)
{
    assert(0 != esize);

    linked_list_t* linked_list = list_allocate();
    if(NULL == linked_list)
    {
        return NULL;
    }

    linked_list->private->head = linked_list->private->tail = NULL;
    linked_list->private->size = 0;
    linked_list->private->esize = esize;

    linked_list->push_front = push_front_cb;
    linked_list->pop_front = pop_front_cb;
    linked_list->push_back = push_back_cb;
    linked_list->pop_back = pop_back_cb;
    linked_list->insert = insert_cb;
    linked_list->extract = extract_cb;
    linked_list->at = at_cb;
    linked_list->erase = erase_cb;
    linked_list->clear = clear_cb;
    linked_list->size = size_cb;    

    return linked_list;
}

void linked_list_delete(linked_list_t** list)
{
    assert(*list);
    assert(list);

    node_t* tmp = (*list)->private->head;

    while (tmp) {
        node_t* next = tmp->next;
        node_free(tmp);
        tmp = next;
    }

    list_free(*list);
    (*list) = NULL;
}
