/**
* \file         memory.c
* \author       Kovalchuk Alexander (roux@yandex.ru)
* \brief        This file contains the prototypes functions which use for...
*/
//_____ I N C L U D E S _______________________________________________________
#include "custom_allocator.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static uint8_t pool[POOL_SIZE] = {0};
static size_t counter = 0;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void* static_malloc(size_t sizemem)
{
	void* buf = NULL;

	if(counter < POOL_SIZE)
	{
		buf = &pool[counter];
		counter += sizemem;
	}

	return buf;
}

void static_free(void * ptrmem)
{
}