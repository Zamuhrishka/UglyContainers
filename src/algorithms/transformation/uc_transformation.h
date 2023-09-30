/**
 * @file    uc_transformation.h
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Transformation functions for converting between containers and arrays.
 *
 * This file provides the implementation of functions to facilitate the
 * transformation between container structures and arrays. The primary
 * objective is to enable seamless conversion in both directions, i.e.,
 * from a container to an array and vice-versa. The functions handle
 * edge cases and ensure that the transformations are performed without
 * data loss, up to the size constraints of the target data structure.
 *
 * @date    2023-09-27
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stddef.h>

#include "core/container.h"
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
  /**
   * \brief Copy all data from container to selected array
   *
   * \param[in] container container from which data would be copied.
   * \param[out] arr array in which data would be copied
   * \param[in] arr_size size of array
   * \return true if all data is copied successfully
   * \return false if data isn`t copied
   */
  bool uc_to_array(const container_t *container, void *arr, size_t arr_size);

  /**
   * \brief Fill container by data from array
   *
   * \param[out] container container for data filling.
   * \param[in] arr array from which data would be copied
   * \param[in] size size of array
   * \return true if all data is copied successfully
   * \return false if data isn`t copied
   */
  bool uc_from_array(container_t *container, const void *arr, size_t size);

/* C++ detection */
#ifdef __cplusplus
}
#endif
