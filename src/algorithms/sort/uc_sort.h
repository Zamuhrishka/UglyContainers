#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stddef.h>

#include "common/contants.h"
#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
/**
 *  \brief List of supported sort methods
 */
typedef enum tagContainerSortTypesEnum
{
  UC_BUBBLE_SORT = 0,
  UC_SELECTION_SORT,
  /* Put new value here */
  UC_LAST_TYPE_SORT
} ContainerSortTypes_e;

/**
 *  \brief List of supported order types
 */
typedef enum SortDir_tag
{
  SORT_ASCENDING = 0,
  SORT_DESCENDING,
} ContainerSortOrder_e;

/**
 * \brief Callback function for data comparions.
 *
 * \note All custom function which will be pass in function in `cmp` argument must follow this prototype.
 */
typedef cmp_t (*compare_fn_t)(const void *data1, const void *data2, size_t esize);

/**
 * \brief Callback function for sort method implementation.
 *
 * \note All custom function which will be pass in function in `sort` argument must follow this prototype.
 */
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
  /**
   * \brief Sort data in selecting container
   *
   * \param[in] container container (mandatory argument).
   * \param[in] sort selected sort method see @ContainerSortTypes_e. This argument isn`t mandatory. In case if user do not give
   *   this argument the default sort function will be used.
   * \param[in] order selected order type see @ContainerSortOrder_e. This argument isn`t mandatory. In case if user do not give
   *   this argument the default order will be used.
   * \param[in] cmp callback fuction which will be used for comparing. This argument isn`t mandatory. In case if user do not give
   *   this argument the default comparision function will be used.
   * \return true if container sorted
   * \return false if fault occur
   */
  bool uc_sort_base(AlgSortArg_t arg);

  /**
   * \brief A special macro that allows you to apply default arguments and a variable list of arguments.
   *
   * \note The use need call tha sort function by this macros calling only.
   *
   * \example
   *
   * ```code
   * bool res = uc_sort(.container = container);
   * ```
   *
   * or
   *
   * ```code
   * bool res = uc_sort(.container = container, .sort=UC_SELECTION_SORT, .order=SORT_DESCENDING);
   * ```
   */
#define uc_sort(...) \
  (uc_sort_base((AlgSortArg_t){.container = NULL, .sort = UC_BUBBLE_SORT, .order = SORT_ASCENDING, .cmp = NULL, __VA_ARGS__}))
/* C++ detection */
#ifdef __cplusplus
}
#endif
