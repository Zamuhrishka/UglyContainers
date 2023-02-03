/**
 * @file msc.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________
#include <stdint.h>
#include <stdbool.h>

#include "core/container.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
bool from_array(container_t* container, void *arr, size_t size, size_t esize);
bool to_array(const container_t* container, void *arr, size_t size, size_t esize);
void to_string(const container_t* container, char* string);

bool unique(container_t* container);
bool fill(container_t* container, size_t start, size_t end, void* value);
container_t* reverse(container_t* container);