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
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static inline bool is_empty(linked_list_t* ll)
{
    return (0 == ll->private->size);
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

    linked_list_t* ll = (linked_list_t*)list;

    // allocate_fn_t mem_allocate = get_allocator();
    // assert(mem_allocate);

    // TODO: Add some align checking?
    // node_t* tmp = (node_t*)mem_allocate(sizeof(node_t));
    // if (NULL == tmp)
    // {
    //     return false;
    // }
    node_t* tmp = node_allocate(ll->private->esize);
    if (NULL == tmp)
    {
        return false;
    }

    // linked_list_t* ll = (linked_list_t*)list;

    // tmp->data = mem_allocate(ll->private->esize);
    // if (NULL == tmp->data)
    // {
    //     free_fn_t mem_free = get_free();
    //     assert(mem_free);
    //     mem_free(tmp);
    //     return false;
    // }

    memcpy(tmp->data, data, ll->private->esize);
    tmp->next = ll->private->head;
    tmp->prev = NULL;

    if (ll->private->head)
    {
        ll->private->head->prev = tmp;
    }

    ll->private->head = tmp;
    if (ll->private->tail == NULL)
    {
        ll->private->tail = tmp;
    }

    ll->private->size++;

    return true;
}

static bool pop_front_cb(void* list, void* data)
{
    assert(list);
    assert(data);

    linked_list_t* ll = (linked_list_t*)list;
    if (is_empty(ll))
    {
        return false;
    }

    node_t* tmp = ll->private->head;
    memcpy(data, ll->private->head->data, ll->private->esize);

    ll->private->head = ll->private->head->next;

    if (ll->private->head)
    {
        ll->private->head->prev = NULL;
    }

    if (tmp == ll->private->tail)
    {
        ll->private->tail = NULL;
    }

    free_fn_t mem_free = get_free();
    assert(mem_free);
    mem_free(tmp);

    ll->private->size--;

    return true;
}

static bool push_back_cb(void* list, const void* data)
{
    assert(list);
    assert(data);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    // TODO: Add some align checking?
    node_t* tmp = (node_t*)mem_allocate(sizeof(node_t));
    if (NULL == tmp)
    {
        return false;
    }

    linked_list_t* ll = (linked_list_t*)list;

    tmp->data = mem_allocate(ll->private->esize);
    if (NULL == tmp->data)
    {
        free_fn_t mem_free = get_free();
        assert(mem_free);
        mem_free(tmp);
        return false;
    }

    memcpy(tmp->data, data, ll->private->esize);
    tmp->next = NULL;
    tmp->prev = ll->private->tail;

    if (ll->private->tail)
    {
        ll->private->tail->next = tmp;
    }

    ll->private->tail = tmp;

    if (ll->private->head == NULL)
    {
        ll->private->head = tmp;
    }

    ll->private->size++;

    return true;
}

static bool pop_back_cb(void* list, void* data)
{
    assert(list);
    assert(data);

    linked_list_t* ll = (linked_list_t*)list;
    if (is_empty(ll))
    {
        return false;
    }

    node_t* tmp = ll->private->tail;

    memcpy(data, tmp->data, ll->private->esize);
    ll->private->tail = ll->private->tail->prev;

    if (ll->private->tail)
    {
        ll->private->tail->next = NULL;
    }

    if (tmp == ll->private->head)
    {
        ll->private->head = NULL;
    }

    free_fn_t mem_free = get_free();
    assert(mem_free);
    mem_free(tmp);

    ll->private->size--;

    return true;
}

static bool insert_cb(void* list, const void* data, size_t index)
{
    assert(list);
    assert(data);

    linked_list_t* ll = (linked_list_t*)list;
    if (index > ll->private->size)
    {
        return false;
    }

    node_t* tmp = node_allocate(ll->private->esize);
    if (NULL == tmp)
    {
        return false;
    }

    node_t* elm = get_nth(ll->private->head, index);
    if (NULL == elm)
    {
        ll->push_front(ll, data);
    }
    else
    {
        memcpy(tmp->data, data, ll->private->esize);
        tmp->prev = elm;
        tmp->next = elm->next;

        if (elm->next)
        {
            elm->next->prev = tmp;
        }
        elm->next = tmp;

        if (!elm->prev)
        {
            ll->private->head = elm;
        }
        if (!elm->next)
        {
            ll->private->tail = elm;
        }
    }

    ll->private->size++;

    return true;
}

static bool at_cb(const void* list, void* data, size_t index)
{
    size_t i = 0;

    assert(list);
    assert(data);

    linked_list_t* ll = (linked_list_t*)list;
    if (index > ll->private->size)
    {
        return false;
    }

    node_t* elm = get_nth(ll->private->head, index);
    if (NULL == elm)
    {
        return false;
    }

    memcpy(data, elm->data, ll->private->esize);

    return true;
}

static bool erase_cb(void* list, size_t index)
{
    assert(list);

    linked_list_t* ll = (linked_list_t*)list;
    if (is_empty(ll))
    {
        return false;
    }

    node_t* elm = get_nth(ll->private->head, index);
    if (NULL == elm)
    {
        return false;
    }

    if (elm->prev)
    {
        elm->prev->next = elm->next;
    }
    if (elm->next)
    {
        elm->next->prev = elm->prev;
    }
    // node_t* tmp = elm->value;

    if (!elm->prev)
    {
        ll->private->head = elm->next;
    }
    if (!elm->next)
    {
        ll->private->tail = elm->prev;
    }

    node_free(elm);

    ll->private->size--;

    return true;
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
    ll->private->head = ll->private->tail = NULL;
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

void linked_list_delete(linked_list_t** list)
{
    return false;
}
