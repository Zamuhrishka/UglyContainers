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

#include "allocator_if.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
typedef struct _Node_tag
{
    void* data;
    struct _Node_tag* next;
} node_t;

struct Private_tag
{
    void* this;
    size_t esize;
    size_t size;
    node_t* head;
};

//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static inline bool is_empty(linked_list_t* ll)
{
    return (NULL == ll->private->head);
}

static inline node_t* get_nth(node_t* head, size_t n)
{
    assert(head);

    size_t counter = 0;
    while (counter < n && head)
    {
        head = head->next;
        counter++;
    }

    return head;
}

static inline node_t* get_last(node_t* head)
{
    if (head == NULL)
    {
        return NULL;
    }

    while (head->next)
    {
        head = head->next;
    }

    return head;
}

static inline node_t* get_last_but_one(node_t* head)
{
    // Only one node in list
    if (head->next == NULL)
    {
        return NULL;
    }

    while (head->next->next)
    {
        head = head->next;
    }

    return head;
}

static bool push_front_cb(void* list, const void* data)
{
    assert(list);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    linked_list_t* ll = (linked_list_t*)list;

    // TODO: Add some align checking?
    node_t* tmp = (node_t*)mem_allocate(sizeof(node_t));
    if (NULL == tmp)
    {
        return false;
    }

    tmp->data = mem_allocate(ll->private->esize);
    if (NULL == tmp->data)
    {
        return false;
    }

    memcpy(tmp->data, data, ll->private->esize);
    tmp->next = ll->private->head;
    ll->private->head = tmp;

    ll->private->size++;

    return true;
}

static bool pop_front_cb(void* list, void* data)
{
    assert(list);
    assert(data);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    linked_list_t* ll = (linked_list_t*)list;
    if (is_empty(ll))
    {
        return false;
    }

    node_t* prev = ll->private->head;
    memcpy(data, ll->private->head->data, ll->private->esize);
    ll->private->head = ll->private->head->next;

    mem_free(prev);

    ll->private->size--;

    return true;
}

static bool push_back_cb(void* list, const void* data)
{
    assert(list);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    linked_list_t* ll = (linked_list_t*)list;
    node_t* last = get_last(ll->private->head);
    node_t* tmp = (node_t*)mem_allocate(sizeof(node_t));

    memcpy(tmp->data, data, ll->private->esize);
    tmp->next = NULL;
    last->next = tmp;

    ll->private->size++;

    return true;
}

static bool pop_back_cb(void* list, void* data)
{
    assert(list);
    assert(data);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    linked_list_t* ll = (linked_list_t*)list;
    if (is_empty(ll))
    {
        return false;
    }

    node_t* lastbn = get_last_but_one(ll->private->head);
    void* pData = (NULL == lastbn) ? ll->private->head->data : lastbn->next->data;
    node_t* active_node = (NULL == lastbn) ? ll->private->head : lastbn->next;

    memcpy(data, pData, ll->private->esize);
    mem_free(active_node);
    active_node = NULL;

    ll->private->size--;

    return true;
}

static bool insert_cb(void* list, const void* data, size_t position)
{
    size_t i = 0;

    assert(list);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    linked_list_t* ll = (linked_list_t*)list;
    if (position > ll->private->size)
    {
        return false;
    }

    while (i < position && ll->private->head->next)
    {
        ll->private->head = ll->private->head->next;
        i++;
    }

    node_t* tmp = (node_t*)mem_allocate(sizeof(node_t));
    if (NULL == tmp)
    {
        return false;
    }

    memcpy(tmp->data, data, ll->private->esize);
    tmp->next = (NULL == ll->private->head->next) ? ll->private->head->next : NULL;
    ll->private->head->next = tmp;

    return true;
}

static bool at_cb(const void* list, void* data, size_t position)
{
    size_t i = 0;

    assert(list);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    linked_list_t* ll = (linked_list_t*)list;
    if (position > ll->private->size)
    {
        return false;
    }

    while (i < position && ll->private->head->next)
    {
        ll->private->head = ll->private->head->next;
        i++;
    }

    memcpy(data, ll->private->head->data, ll->private->esize);

    return true;
}

static bool erase_cb(void* list, size_t position)
{
    return false;
}

static size_t size_cb(const void* list)
{
    assert(list);

    linked_list_t* ll = (linked_list_t*)list;
    return ll->private->size;
}

//_____ P U B L I C  F U N C T I O N S_________________________________________
linked_list_t* linked_list_create(size_t esize)
{
    assert(0 != esize);

    if (!is_allocator_valid())
    {
        return false;
    }

    allocate_fn_t mem_allocate = get_allocator();
    free_fn_t mem_free = get_free();

    // TODO: Add some align checking?
    linked_list_t* ll = (linked_list_t*)mem_allocate(sizeof(linked_list_t));
    if (NULL == ll)
    {
        return NULL;
    }

    private_t* member = (private_t*)mem_allocate(sizeof(private_t));
    if (NULL == member)
    {
        mem_free(ll);
        return NULL;
    }

    ll->private = member;
    ll->private->this = ll;
    ll->private->head = NULL;
    ll->private->size = 0;
    ll->private->esize = esize;

    ll->push_front = push_front_cb;
    ll->pop_front = pop_front_cb;
    ll->push_back = push_back_cb;
    ll->pop_back = pop_back_cb;
    ll->insert = insert_cb;
    ll->at = at_cb;
    ll->erase = erase_cb;
    ll->size = size_cb;

    return ll;
}

bool linked_list_delete(linked_list_t** list)
{
    return false;
}
