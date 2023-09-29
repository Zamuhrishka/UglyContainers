#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stddef.h>

#include "common/contants.h"
#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
/**
 *  \brief
 */
typedef enum tagContainerSortTypesEnum
{
  UC_BUBBLE_SORT = 0,
  UC_SELECTION_SORT,

  UC_LAST_TYPE_SORT
} ContainerSortTypes_e;

/**
 *  \brief
 */
typedef enum SortDir_tag
{
  SORT_ASCENDING = 0,
  SORT_DESCENDING,
} ContainerSortOrder_e;

typedef cmp_t (*compare_fn_t)(const void *data1, const void *data2, size_t esize);
typedef void (*sort_fn_t)(void *arr, size_t size, size_t esize, compare_fn_t cmp, ContainerSortOrder_e order);

typedef struct
{
  container_t *container;
  ContainerSortTypes_e sort;
  ContainerSortOrder_e order;
  compare_fn_t cmp;
} AlgSortArg_t;

//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/* C++ detection */
#ifdef __cplusplus
extern "C"
{
#endif
  bool uc_sort_base(AlgSortArg_t arg);
#define uc_sort(...) \
  (uc_sort_base((AlgSortArg_t){.container = NULL, .sort = UC_BUBBLE_SORT, .order = SORT_ASCENDING, .cmp = NULL, __VA_ARGS__}))
/* C++ detection */
#ifdef __cplusplus
}
#endif
