/**
 * @file    equal.h
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Utility functions for comparing containers for equality.
 * @date    2023-09-28
 *
 * This header file provides the definitions and prototypes of functions that
 * facilitate the comparison of two containers for equality. The primary function,
 * `uc_equal_base`, evaluates whether the contents of two containers are the same,
 * using a custom comparison function if provided. Otherwise, a default comparison
 * method is employed.
 *
 * The file also introduces a type for the comparison function and a convenient macro
 * that simplifies the use of the `uc_equal_base` function by applying default
 * arguments.
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stdint.h>

#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
/**
 * \brief Callback function for data comparions.
 *
 * \note All custom function which will be pass in function in `cmp` argument must follow this prototype.
 */
typedef bool (*equal_fn_t)(const void *data1, const void *data2, size_t esize);

/**
 * \brief The `uc_equal_base` function argument structure
 *
 */
typedef struct
{
  const container_t *container1;
  const container_t *container2;
  equal_fn_t cmp;
} AlgEqualArg_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/* C++ detection */
#ifdef __cplusplus
extern "C"
{
#endif
  /**
   * \brief Checks two containers for equality
   *
   * \param[in] container1.First container (mandatory argument).
   * \param[in] container2.Second container (mandatory argument).
   * \param[in] cmp callback fuction which will be used for comparing.This argument isn`t mandatory. In case if user do not give
   *   this argument the default comparision function will be used.
   * \return true if container are equal
   * \return false if container aren`t equal
   */
  bool uc_equal_base(AlgEqualArg_t arg);

  /**
   * \brief A special macro that allows you to apply default arguments and a variable list of arguments.
   *
   * \note The use need call tha compare function by this macros calling only.
   *
   * \example
   *
   * ```code
   * bool res = uc_equal(.container1 = container1, .container2 = container2);
   * ```
   */
#define uc_equal(...) (uc_equal_base((AlgEqualArg_t){.container1 = NULL, .container2 = NULL, .cmp = NULL, __VA_ARGS__}))
/* C++ detection */
#ifdef __cplusplus
}
#endif
