/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "config.h"

#if CONTAINER_TYPE == LINKED_LIST
    #include "linked_list/linked_list.h"
#elif CONTAINER_TYPE == VECTOR
    #include "vector/vector.h"
#else
    #error "You have to define core container type by set #CONTAINER_TYPE=="
#endif
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Container_tag;
typedef struct Container_tag container_t;
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void container_init(allocate_fn_t alloc_cb, free_fn_t free_cb);
container_t* container_create(size_t esize);
void container_delete(container_t** list);
bool container_push_front(container_t* container, const void* data);
bool container_pop_front(container_t* container, void* data);
bool container_push_back(container_t* container, const void* data);
bool container_pop_back(container_t* container, void* data);
bool container_insert(container_t* container, const void* data, size_t position);
bool container_at(const container_t* container, void* data, size_t position);
bool container_erase(container_t* container, size_t position);
size_t container_size(const container_t* container);