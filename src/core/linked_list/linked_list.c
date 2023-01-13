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

#include "contants.h"
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


struct ll_tag
{
    struct member {
        void* this;
        size_t elem_size;
        size_t list_size;
        node_t* head;
    };

    struct magic_methods
    {
        void (*str)(void* value, char* str);
        cmp_t (*compare)(void* value1, void* value2);
    };
    
    struct interface
    {
        bool (*push_front)(void* this, const void* data);
        bool (*pop_front)(void* this, void* data);
        bool (*push_back)(void* this, const void* data);
        bool (*pop_back)(void* this, void* data);
        bool (*insert)(void* this, const void* data, size_t position);
        bool (*erase)(void* this, size_t position);
    };    
};
//_____ M A C R O S ___________________________________________________________
//TODO: Macros as template


//PUSH_FRONT(list, data)        (list##->push_front((void*)list, &data))
//_____ V A R I A B L E S _____________________________________________________
/// Pointer to the memory allocation function
static void* (*mem_allocate)(size_t size) = NULL;

/// Pointer to the memory free function
static void (*mem_free) (void *pointer) = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static inline cmp_t compare_u8(void* value1, void* value2)
{
    
}

// static inline cmp_t compare_u8(void* value1, void* value2)
// {
    
// }

// static inline cmp_t compare_u16()
// {
    
// }

// static inline cmp_t compare_u32()
// {
    
// }

// static inline cmp_t compare_u64()
// {
    
// }

static inline bool callbacks_is_valid(void)
{
    return (mem_allocate != NULL && mem_free != NULL);
}

static inline bool is_empty(linked_list_t* ll)
{
    return (NULL != ll->member.head);
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


static bool sll_push_front(void* list, const void* data)
{
    assert(NULL != list);
    assert(NULL != data);

    linked_list_t* ll  = (linked_list_t*)list;

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

static bool sll_pop_front(void* list, void* data)
{
    assert(NULL != list);
    assert(NULL != data);

    linked_list_t* ll  = (linked_list_t*)list;

    if (is_empty(ll)) {
        return false;
    }

    node_t* prev = ll->head;
    memcpy(data, ll->head->data, ll->elem_size);
    ll->head = ll->head->next;

    mem_free(prev);

    return true;
}


static bool sll_push_back(void* list, const void* data)
{
    assert(NULL != list);
    assert(NULL != data);

    linked_list_t* ll  = (linked_list_t*)list;

    node_t *last = get_last(ll->head);
    node_t *tmp = (node_t*) mem_allocate(sizeof(node_t));

    memcpy(tmp->data, data, ll->elem_size);
    tmp->next = NULL;

    last->next = tmp;

    return true;
}

static bool sll_pop_back(void* list, void* data)
{
    assert(NULL != list);
    assert(NULL != data);

    linked_list_t* ll  = (linked_list_t*)list;

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

static bool sll_insert(void* list, const void* data, size_t position)
{
    size_t i = 0;

    assert(NULL != list);
    assert(NULL != data);

    linked_list_t* ll  = (linked_list_t*)list;

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


void compare_callback_register(linked_list_t* list, cmp_t (*compare)(void* value1, void* value2))
{

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

    ll->this = ll;
	ll->head = NULL;
	ll->list_size = 0;
	ll->elem_size = data_size;

    ll->push_front = sll_push_front;
    ll->pop_front = sll_pop_front;
    ll->push_back = sll_push_back;
    ll->pop_back = sll_pop_back;
    ll->insert = sll_insert;
    ll->erase = NULL;

	return ll;
}

bool ll_delete(linked_list_t **list)
{
    return false;
}



// linked_list_t* list = ll_create(sizeof(uint32_t));

// uint32_t data = 0x55555555;
// list->push_front((void*)list, &data);

//PUSH_FRONT(list, data);
