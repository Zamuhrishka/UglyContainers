/**
 * @file equal.h
 * @author Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-09-28
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stdint.h>

#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
typedef bool (*equal_fn_t)(const void *data1, const void *data2, size_t esize);

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
  bool container_equal(AlgEqualArg_t arg);
#define equal(...) (container_equal((AlgEqualArg_t){.container1 = NULL, .container2 = NULL, .cmp = NULL, __VA_ARGS__}))
/* C++ detection */
#ifdef __cplusplus
}
#endif
