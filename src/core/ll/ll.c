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
typedef struct node_tag
{
	lldata_t value;
	struct _Node *next;
	struct _Node *prev;
} node_t;

/**
* @brief  	This structure describe the doubly-linked list.
*
* @element	size - size of list;
* @element	*head - up limit;
* @element	*tail - low limit;
*/
struct linked_list_tag {
	size_t size;
	struct _Node *head;
	struct _Node *tail;
};
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
//!Pointer to the memory allocation function
static void* (*ll_mem_alloc)(size_t sizemem) = NULL;

//!Pointer to the memory free function
static void (*ll_mem_free) (void *ptrmem) = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
/**
* @brief 	This function is checking list for empty state.
*
* @param  	*list[in] - pointer to doubly-linked list.
*
* @return 	Pointer to the nth node of list or NULL.
*/
inline static bool ll_is_empty(linked_list_t* list)
{
	return ((list->size == 0) && ((list->head->prev == NULL) && (list->tail->next == NULL))) ? true : false;
}

/**
* @brief 	Return pointer to the nth node of list.
*
* @param  	*list[in] - pointer to list.
* @param  	index[in] - number of searching node.
*
* @return 	Pointer to the nth node of list or NULL.
*/
static node_t* ll_get_nth(linked_list_t* list, size_t index)
{
	node_t *tmp = list->head->next;

	if((list == NULL) || (index > list->size)) {
		return NULL;
	}

	for(size_t i = 0; i < index; i++) {
		tmp = tmp->next;
	}

	return tmp;
}
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
	ll_mem_alloc = custom_malloc;
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
	ll_mem_free = custom_free;
}

/**
* @brief 	Create new linked list.
*
* @param  	none.
*
* @return 	pointer to new list.
*/
linked_list_t* ll_create(void)
{
	if(ll_mem_alloc == NULL || ll_mem_free == NULL) {
		return NULL;
	}

	linked_list_t *tmp = (linked_list_t*) ll_mem_alloc(sizeof(linked_list_t));
	if(tmp == NULL) {
		return NULL;
	}

	node_t *head = (node_t*) ll_mem_alloc(sizeof(node_t));
	if(head == NULL)
	{
		ll_mem_free(tmp);
		return NULL;
	}

	node_t *tail = (node_t*) ll_mem_alloc(sizeof(node_t));
	if(tail == NULL)
	{
		ll_mem_free(tmp);
		ll_mem_free(head);
		return NULL;
	}

	head->next = tail;
	head->prev = NULL;
	head->value = 0;

	tail->next = NULL;
	tail->prev = head;
	tail->value = 0;

	tmp->head = head;
	tmp->tail = tail;
	tmp->size = 0;

	return tmp;
}

/**
* @brief 	Create linked list from array.
*
* @param  	*list[in] - pointer to list.
* @param  	*arr[in] - pointer to source array.
* @param  	size[in] - size of array.
*
* @return 	true/false.
*/
// bool ll_from_array(linked_list_t *list, const lldata_t *arr, size_t size)
// {
// 	if (arr == NULL || size == 0 || list == NULL) {
// 		return false;
// 	}

//     do {
//         ll_push(list, arr[--size]);
//     } while(size);

//     return true;
// }

/**
* @brief 	Create array from linked list.
*
* @param  	*list[in] - pointer to list.
* @param  	*arr[out] - pointer to out array.
* @param  	size[in] - size of array.
*
* @return 	true/false.
*/
// bool ll_to_array(linked_list_t *list, lldata_t* arr, size_t size)
// {
// 	size_t length = 0;

// 	if(size == 0 || arr == NULL || list == NULL) {
// 		return false;
// 	}

// 	length = ll_length(list);
// 	if(length > size || length == 0) {
// 		return false;
// 	}

// 	for(size_t i = 0; i < length; i++) {
// 		if(ll_pop(list, &arr[i]) == false) {
// 			return false;
// 		}
// 	}

// 	return true;
// }

/**
* @brief 	Delete list.
*
* @param  	**list[in] - pointer to list.
*
* @return 	true/false.
*/
bool ll_delete(linked_list_t **list)
{
	node_t *tmp = (*list)->head->next;
	node_t *next = NULL;
	while (tmp) {
		next = tmp->next;
		ll_mem_free(tmp);
		tmp = next;
	}

	ll_mem_free((*list)->tail);
	ll_mem_free((*list)->head);
	ll_mem_free(*list);
	(*list) = NULL;

    return true;
}

/**
* @brief 	Add new node on top of list.
*
* @param  	*list[in] - pointer to list.
* @param  	data[in] - data for new node of list.
*
* @return 	true/false.
*/
bool ll_push(linked_list_t *list, lldata_t data)
{
	node_t *tmp = NULL;

	if ((list == NULL)) {
		return false;
	}

	tmp = (node_t*) ll_mem_alloc(sizeof(node_t));
	if (tmp == NULL) {
		return false;
	}

	tmp->value = data;
	tmp->next = list->head->next;
	tmp->prev = list->head;

	if(list->head->next != NULL) {
		list->head->next->prev = tmp;
	}
	list->head->next = tmp;

	if (list->tail->prev == NULL) {
		list->tail->prev = tmp;
	}

	list->size++;

    return true;
}

/**
* @brief 	Delete node on top and return it value.
*
* @param  	*list[in] - pointer to list.
* @param  	*data[out] - value of deleted HEAD node.
*
* @return 	true/false.
*/
bool ll_pop(linked_list_t *list, lldata_t *data)
{
	node_t* prev = NULL;

	if ((list == NULL) || (ll_is_empty(list))) {
		return false;
	}

	prev = list->head->next;
	list->head->next = prev->next;

	prev->next->prev = list->head;
	if (prev == list->tail->prev) {
		list->tail->prev = NULL;
	}

	*data = prev->value;
	ll_mem_free(prev);

	list->size--;
	return true;
}

/**
* @brief 	Add new node to the end of list.
*
* @param  	*list[in] - pointer to list.
* @param  	data[in] - value of new node.
*
* @return 	true/false.
*/
bool ll_enqueue(linked_list_t *list, lldata_t data)
{
	node_t *tmp = NULL;

	if ((list == NULL)) {
		return false;
	}

	tmp = (node_t*) ll_mem_alloc(sizeof(node_t));
	if (tmp == NULL) {
		return false;
	}

	tmp->value = data;
	tmp->next = list->tail;
	tmp->prev = list->tail->prev;

	list->tail->prev->next = tmp;
	list->tail->prev = tmp;

	if (list->head->next == NULL) {
		list->head->next = tmp;
	}
	list->size++;

	return true;
}

/**
* @brief 	Delete the last node of list.
*
* @param  	*list[in] - pointer to list.
* @param  	*data[out] - value of new node.
*
* @return 	true/false.
*/
bool ll_dequeue(linked_list_t *list, lldata_t *data)
{
	node_t *next;

	if ((list == NULL) || (ll_is_empty(list))) {
		return false;
	}

	next = list->tail->prev;
	list->tail->prev = next->prev;

	next->prev->next = list->tail;
	if (next == list->head->next) {
		list->head->next = NULL;
	}

	*data = next->value;
	ll_mem_free(next);

	list->size--;
	return true;
}

/**
* @brief 	Insert node with value in to list on position index.
*
* @param  	*list[in] - pointer to list.
* @param  	value[in] - value of new node.
* @param  	index[in] - position in list.
*
* @return 	true/false.
*/
bool ll_insert(linked_list_t *list, size_t index, lldata_t value)
{
	node_t *elm = NULL;
	node_t *tmp = NULL;
	size_t len = ll_length(list);

	if(list == NULL || index > len) {
		return false;
	}

	elm = ll_get_nth(list, index);
	if (elm == NULL) {
		return false;
	}

	tmp = (node_t*) ll_mem_alloc(sizeof(node_t));
	if(tmp == NULL) {
		return false;
	}

	tmp->value = value;
	tmp->next = elm;
	tmp->prev = elm->prev;

	elm->prev->next = tmp;
	elm->prev = tmp;

	list->size++;

    return true;
}

/**
* @brief 	Delete node with n position from list. And return it value.
*
* @param  	*list[in] - pointer to list.
* @param  	*value[out] - value of deleted node.
* @param  	index[in] - position in list.
*
* @return 	true/false.
*/
bool ll_extract(linked_list_t *list, size_t index, lldata_t* value)
{
	node_t *elm = NULL;
	size_t len = ll_length(list);

	if(list == NULL || index > len) 	{
		return false;
	}

	elm = ll_get_nth(list, index);
	if (elm == NULL) {
		return false;
	}

	*value = elm->value;
	elm->prev->next = elm->next;
	elm->next->prev = elm->prev;

	ll_mem_free(elm);
	list->size--;

    return true;
}

/**
* @brief 	Calculate size of list.
*
* @param  	*list[in] - pointer to list.
*
* @return 	size of list.
*/
size_t ll_length(const linked_list_t *list)
{
	return list->size;
}

