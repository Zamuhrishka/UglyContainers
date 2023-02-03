/**
 * @file sort.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-26
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________
#include "core/container.h"
#include "contants.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
/**
*  \brief
*/
typedef enum SortDir_tag {
    SORT_ASCENDING = 0,
    SORT_DESCENDING,
} sort_dir_e;

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void sort(container_t* container, sort_dir_e direction, cmp_t (cmp*)(void*, void*));