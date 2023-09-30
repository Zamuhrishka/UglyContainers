/**
 * @file mem_alloc_stub.h
 * @author Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-09-30
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/* C++ detection */
#ifdef __cplusplus
extern "C"
{
#endif
  void *mem_allocate_fault(size_t size);
  void *mem_allocate(size_t size);
  void mem_free(volatile void *pointer);
/* C++ detection */
#ifdef __cplusplus
}
#endif
