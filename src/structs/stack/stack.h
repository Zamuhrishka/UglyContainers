/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"

#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
typedef container_t stack_t;
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
stack_t* stack_create(size_t esize);
void stack_delete(stack_t** stack);
bool stack_push(stack_t* stack, const void* data);
bool stack_pop(stack_t* stack, void* data);
bool stack_peek(const stack_t* stack, void* data);
bool stack_size(const stack_t* stack);