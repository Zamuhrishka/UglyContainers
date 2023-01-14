/**
 * @file
 * @author learnc.info@gmail.com (https://learnc.info/adt/linked_list.html)
 *          Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief  Double-linked list
 * @date 2023-01-01
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "stdbool.h"
#include "stdint.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Private_tag;
typedef struct Private_tag private_t;

typedef struct
{
    private_t* private;
    struct public
    {
        bool (*push_front)(void* this, const void* data);
        bool (*pop_front)(void* this, void* data);
        bool (*push_back)(void* this, const void* data);
        bool (*pop_back)(void* this, void* data);
        bool (*insert)(void* this, const void* data, size_t position);
        bool (*at)(const void* this, void* data, size_t position);
        bool (*erase)(void* this, size_t position);
        size_t (*size)(const void* this);
    };
} linked_list_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * @brief 	Create new linked list.
 *
 * @param  	none.
 *
 * @return 	pointer to new list.
 */
linked_list_t* linked_list_create(size_t esize);

/**
 * @brief 	Delete list.
 *
 * @param  	**list[in] - pointer to list.
 *
 * @return 	true/false.
 */
void linked_list_delete(linked_list_t** list);
