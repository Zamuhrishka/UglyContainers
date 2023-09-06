/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-02-01
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________
#include <stdint.h>
#include <stdbool.h>
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Set_tag;
typedef struct Set_tag set_t;
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
set_t* set_create(size_t size, size_t esize, bool (*equal)(void*, void*));
void set_delete(set_t* set);
bool set_add(set_t* set, void* data);
bool set_remove(set_t* set, void* data);
bool set_contain(set_t* set, void* data);
size_t set_size(set_t* set);