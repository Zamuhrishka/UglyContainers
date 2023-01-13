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
    struct {
        void* this;
        size_t elem_size;
        size_t list_size;
        node_t* head;
    }   member;

    struct magic
    {
        void (*str)(void* value, char* str);
        void (*compare)(void* value1, void* value2);
    };
    


    struct
    {
        bool (*push_front)(void* this, const void* data);
        bool (*pop_front)(void* this, void* data);
        bool (*push_back)(void* this, const void* data);
        bool (*pop_back)(void* this, void* data);
        bool (*insert)(void* this, const void* data, size_t position);
        bool (*erase)(void* this, size_t position);
    }   methods;    
};
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
/// Pointer to the memory allocation function
static void* (*mem_allocate)(size_t size) = NULL;

/// Pointer to the memory free function
static void (*mem_free) (void *pointer) = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static inline bool compare_u8()
{

}

static inline bool compare_u16()
{
    
}

static inline bool compare_u32()
{
    
}

static inline bool compare_u64()
{
    
}


//TODO: Macros as template

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
    tmp->data = mem_allocate(ll->member.elem_size);
    if(NULL == tmp->data) {
		return false;
	}

    memcpy(tmp->data, data, ll->member.elem_size);
    tmp->next = ll->member.head;
    ll->member.head = tmp;
}

static bool sll_pop_front(void* list, void* data)
{
    assert(NULL != list);
    assert(NULL != data);

    linked_list_t* ll  = (linked_list_t*)list;

    if (is_empty(ll)) {
        return false;
    }

    node_t* prev = ll->member.head;
    memcpy(data, ll->member.head->data, ll->member.elem_size);
    ll->member.head = ll->member.head->next;

    mem_free(prev);

    return true;
}


static bool sll_push_back(void* list, const void* data)
{
    assert(NULL != list);
    assert(NULL != data);

    linked_list_t* ll  = (linked_list_t*)list;

    node_t *last = get_last(ll->member.head);
    node_t *tmp = (node_t*) mem_allocate(sizeof(node_t));

    memcpy(tmp->data, data, ll->member.elem_size);
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
     
    node_t* lastbn = get_last_but_one(ll->member.head);
    void* pData = (NULL == lastbn) ? ll->member.head->data : lastbn->next->data;
    node_t* active_node = (NULL == lastbn) ? ll->member.head : lastbn->next;

    memcpy(data, pData, ll->member.elem_size);
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

    while (i < position && ll->member.head->next) {
        ll->member.head = ll->member.head->next;
        i++;
    }

    node_t* tmp = (node_t*) malloc(sizeof(node_t));
    if(NULL == tmp) {
        return false;
    }

    memcpy(tmp->data, data, ll->member.elem_size);
    tmp->next = (NULL == ll->member.head->next) ? ll->member.head->next : NULL;
    ll->member.head->next = tmp;
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

    ll->member.this = ll;
	ll->member.head = NULL;
	ll->member.list_size = 0;
	ll->member.elem_size = data_size;

    ll->methods.push_front = sll_push_front;
    ll->methods.pop_front = sll_pop_front;
    ll->methods.push_back = sll_push_back;
    ll->methods.pop_back = sll_pop_back;
    ll->methods.insert = sll_insert;
    ll->methods.erase = NULL;

	return ll;
}

bool ll_delete(linked_list_t **list)
{
    return false;
}



linked_list_t* list = ll_create(sizeof(uint32_t));

uint32_t data = 0x55555555;
list->push_front((void*)list, &data);
