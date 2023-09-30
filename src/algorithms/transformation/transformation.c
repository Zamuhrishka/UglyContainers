/**
 * @file    transformation.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Transformation functions for converting between containers and arrays.
 * @date    2023-09-27
 */

//_____ I N C L U D E S _______________________________________________________
#include "transformation.h"

#include "common/uc_assert.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * Copy all data from container to selected array.
 *
 * Detailed description see in transformation.h
 */
bool uc_to_array(const container_t *container, void *arr, size_t size)
{
  UC_ASSERT(container && "Invalid argument: container");
  UC_ASSERT(arr && "Invalid argument: arr");
  UC_ASSERT(size && "Invalid argument: size");

  size_t c_size = container_size(container);
  size_t len = (c_size >= size) ? size : c_size;

  for (size_t i = 0; i < len; i++)
  {
    if (!container_at(container, (arr + (container_esize(container) * i)), i))
    {
      return false;
    }
  }

  return true;
}

/**
 * Fill container by data from array.
 *
 * Detailed description see in transformation.h
 */
bool uc_from_array(container_t *container, const void *arr, size_t size)
{
  UC_ASSERT(container && "Invalid argument: container");
  UC_ASSERT(arr && "Invalid argument: arr");
  UC_ASSERT(size && "Invalid argument: size");

  for (size_t i = 0; i < size; i++)
  {
    if (!container_push_back(container, (void *)(arr + (container_esize(container) * i))))
    {
      return false;
    }
  }

  return true;
}
