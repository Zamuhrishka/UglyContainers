/**
 * @file    mem_alloc_stub.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date    2023-09-30
 */

//_____ I N C L U D E S _______________________________________________________
#include "mem_alloc_stub.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static uint8_t array[10] = {0};
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void *mem_allocate_fault(size_t size)
{
  return NULL;
}

void *mem_allocate(size_t size)
{
  return array;
}

void mem_free(volatile void *pointer) {}
