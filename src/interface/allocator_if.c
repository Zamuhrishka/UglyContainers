/**
 * \file
 * \author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief
 * \date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "interface/allocator_if.h"

#include "common/uc_assert.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
/// Pointer to the memory allocation function
static void* (*mem_allocate)(size_t size) = malloc;

/// Pointer to the memory free function
static void (*mem_free)(volatile void* pointer) = free;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * This function register memory allocation function.
 *
 * Detailed description see in allocator_if.h
 */
void allocation_cb_register(allocate_fn_t alloc_cb)
{
  UC_ASSERT(alloc_cb);
  mem_allocate = alloc_cb;
}

/**
 * This function register memory free function.
 *
 * Detailed description see in allocator_if.h
 */
void free_cb_register(free_fn_t free_cb)
{
  UC_ASSERT(free_cb);
  mem_free = free_cb;
}

/**
 * Get the allocator function
 *
 * Detailed description see in allocator_if.h
 */
allocate_fn_t get_allocator(void)
{
  return mem_allocate;
}

/**
 * Get the free function
 *
 * Detailed description see in allocator_if.h
 */
free_fn_t get_free(void)
{
  return mem_free;
}

/**
 * Check is allocator functions is valid
 *
 * Detailed description see in allocator_if.h
 */
bool is_allocator_valid(void)
{
  return (mem_allocate != NULL && mem_free != NULL);
}
