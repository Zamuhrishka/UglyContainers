/**
 * @file ll.c
 * @author learnc.info@gmail.com (https://learnc.info/adt/linked_list.html)
 *         Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief Double-linked list
 * @date 2023-01-01
 */

//_____ I N C L U D E S _______________________________________________________
#include "ll.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
/**
* @brief  	This structure describe the Node of doubly-linked list.
*
* @element	value - value of node;
* @element	*next - pointer to the next node;
* @element	*prev - pointer to the prev node;
*/
typedef struct _Node_tag
{
	void* data;
	struct _Node_tag* next;
} node_t;


struct linked_list_tag
{
	size_t elem_size;
	size_t list_size;
	node_t* head;

    void (*create)(size_t data_size);
    void (*delete)(void);
    bool (*push_front)(const void* data);
    bool (*pop_front)(void* data);
    bool (*push_back)(const void* data);
    bool (*pop_back)(void* data);
    bool (*insert)(const void* data, size_t position);
    bool (*erase)(size_t position);
};
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
/// Pointer to the memory allocation function
static void* (*mem_allocate)(size_t size) = NULL;

/// Pointer to the memory free function
static void (*mem_free) (void *pointer) = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static inline bool callbacks_is_valid(void)
{
    return (mem_allocate != NULL && mem_free != NULL);
}

static inline bool is_empty(sll_t* ll)
{
    return (NULL != ll->head);
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

static inline node_t* get_last(node_t *head) 
{
    if (head == NULL) {
        return NULL;
    }

    while (head->next) {
        head = head->next;
    }

    return head;
}

static inline node_t* get_last_but_one(node_t* head) 
{
    //Only one node in list
    if (head->next == NULL) {
        return NULL;
    }

    while (head->next->next) {
        head = head->next;
    }

    return head;
}




bool sll_push_front(sll_t* ll, const void* data)
{
    assert(NULL != ll);
    assert(NULL != data);

    //TODO: Add some align checking?
    node_t* tmp = (node_t*) mem_allocate(sizeof(node_t));
    if(NULL == tmp) {
        return false;
    }

    //TODO: Add some align checking?
    tmp->data = mem_allocate(ll->elem_size);
    if(NULL == tmp->data) {
		return false;
	}

    memcpy(tmp->data, data, ll->elem_size);
    tmp->next = ll->head;
    ll->head = tmp;
}

bool sll_pop_front(sll_t* ll, void* data)
{
    assert(NULL != ll);
    assert(NULL != data);

    if (is_empty(ll)) {
        return false;
    }

    node_t* prev = ll->head;
    memcpy(data, ll->head->data, ll->elem_size);
    ll->head = ll->head->next;

    mem_free(prev);

    return true;
}


bool sll_push_back(sll_t* ll, const void* data)
{
    assert(NULL != ll);
    assert(NULL != data);

    node_t *last = get_last(ll->head);
    node_t *tmp = (node_t*) mem_allocate(sizeof(node_t));

    memcpy(tmp->data, data, ll->elem_size);
    tmp->next = NULL;

    last->next = tmp;

    return true;
}

bool sll_pop_back(sll_t* ll, void* data)
{
    assert(NULL != ll);
    assert(NULL != data);

    if (is_empty(ll)) {
        return false;
    }
     
    node_t* lastbn = get_last_but_one(ll->head);
    void* pData = (NULL == lastbn) ? ll->head->data : lastbn->next->data;
    node_t* active_node = (NULL == lastbn) ? ll->head : lastbn->next;

    memcpy(data, pData, ll->elem_size);
    mem_free(active_node);
    active_node = NULL;

    return true;
}



bool sll_insert(sll_t* ll, const void* data, size_t position)
{
    size_t i = 0;

    while (i < position && ll->head->next) {
        ll->head = ll->head->next;
        i++;
    }

    node_t* tmp = (node_t*) malloc(sizeof(node_t));
    if(NULL == tmp) {
        return false;
    }

    memcpy(tmp->data, data, ll->elem_size);
    tmp->next = (NULL == ll->head->next) ? ll->head->next : NULL;
    ll->head->next = tmp;
}

// bool sll_erase(sll_t* ll, size_t position)
// {
//     if (position == 0) 
//     {
//         return sll_pop_front(ll, void* data);
//     } 
//     else 
//     {
//         Node *prev = getNth(*head, n-1);
//         Node *elm  = prev->next;
//         int val = elm->value;
 
//         prev->next = elm->next;
//         free(elm);
//         return val;
//     }
// }
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
* @brief 	This function register memory allocation function.
*
* 			The registration function will be use for allocation memory
* 			for list store.
*
* 			@warning You must register allocation function before call any
* 			function this library.
*
* 			@example ll_alloc_callback_reg(&malloc);
*
* @param  	*custom_malloc[in] - pointer to the memory allocation function.
*
* @return 	none.
*/
void ll_alloc_callback_reg(void* (*custom_malloc)(size_t sizemem))
{
	mem_allocate = custom_malloc;
}

/**
* @brief 	This function register memory free function.
*
* 			The registration function will be use for free memory
* 			of list.
*
* 			@warning You must register free function before call any
* 			function this library.
*
* 			@example ll_free_callback_reg(&free);
*
* @param  	*custom_free[in] - pointer to the memory free function.
*
* @return 	none.
*/
void ll_free_callback_reg(void (*custom_free)(void * ptrmem))
{
	mem_free = custom_free;
}

linked_list_t* ll_create(size_t data_size)
{
	if(!callbacks_is_valid()) {
		return NULL;
	}

    //TODO: Add some align checking?
	linked_list_t *ll = (linked_list_t*)mem_allocate(sizeof(linked_list_t));
	if(NULL == ll) {
		return NULL;
	}

	ll->head = NULL;
	ll->list_size = 0;
	ll->elem_size = data_size;

	return ll;
}
