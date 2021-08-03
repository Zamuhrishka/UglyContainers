/**
* \file         memory.h
* \author       Kovalchuk Alexander (roux@yandex.ru)
* \brief        This file contains the prototypes functions which use for...
*/

#pragma once

/* C++ detection */
#ifdef __cplusplus
    extern "C" {
#endif
//_____ I N C L U D E S _______________________________________________________
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
//_____ C O N F I G S  ________________________________________________________
#define POOL_SIZE                          5000U                                //< Max count of available queues
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void* static_malloc(size_t sizemem);
void static_free(void * ptrmem);

/* C++ detection */
#ifdef __cplusplus
}
#endif