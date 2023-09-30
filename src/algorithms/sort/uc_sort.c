//_____ I N C L U D E S _______________________________________________________
#include "uc_sort.h"

#include "common/uc_assert.h"
#include "interface/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
static void bubble_sort(void *arr, size_t size, size_t esize, compare_fn_t cmp, ContainerSortOrder_e order);
static void selection_sort(void *arr, size_t size, size_t esize, compare_fn_t cmp, ContainerSortOrder_e order);
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static sort_fn_t sorts_callbacks[UC_LAST_TYPE_SORT] = {bubble_sort, selection_sort};
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static cmp_t default_compare(const void *value1, const void *value2, size_t esize)
{
  return (cmp_t)memcmp(value1, value2, esize);
}

static void bubble_sort(void *arr, size_t size, size_t esize, compare_fn_t cmp, ContainerSortOrder_e order)
{
  cmp_t _order = (order == SORT_ASCENDING) ? GT : LE;
  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  void *tmp = (void *)mem_allocate(esize);

  for (int i = 0; i < size - esize; i = i + esize)
  {
    for (int j = 0; j < size - i - esize; j = j + esize)
    {
      void *ndata1 = ((uint8_t *)arr + j);
      void *ndata2 = ((uint8_t *)arr + j + esize);

      if (cmp(ndata1, ndata2, esize) == _order)
      {
        memcpy(tmp, ndata1, esize);
        memcpy(ndata1, ndata2, esize);
        memcpy(ndata2, tmp, esize);
      }
    }
  }

  mem_free(tmp);
}

static void selection_sort(void *arr, size_t size, size_t esize, compare_fn_t cmp, ContainerSortOrder_e order)
{
  cmp_t _order = (order == SORT_ASCENDING) ? LE : GT;

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  void *tmp = (void *)mem_allocate(esize);

  for (size_t i = 0; i < size - esize; i = i + esize)
  {
    size_t min_idx = i;
    void *data_j = NULL;
    void *data_idx = NULL;

    int j = 0;
    for (j = i + esize; j < size; j = j + esize)
    {
      data_j = ((uint8_t *)arr + j);
      data_idx = ((uint8_t *)arr + min_idx);

      if (cmp(data_j, data_idx, esize) == _order)
      {
        min_idx = j;
      }
    }

    data_j = ((uint8_t *)arr + j);
    data_idx = ((uint8_t *)arr + min_idx);

    void *data_i = ((uint8_t *)arr + i);
    memcpy(tmp, data_idx, esize);
    memcpy(data_idx, data_i, esize);
    memcpy(data_i, tmp, esize);
  }

  for (size_t i = 0; i < size - esize; i = i + esize)
  {
    void *data = ((uint8_t *)arr + i);
  }

  mem_free(tmp);
}

//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * ort data in selecting container.
 *
 * Detailed description see in uc_sort.h
 */
bool uc_sort_base(AlgSortArg_t arg)
{
  // bool status = true;
  compare_fn_t compare = (arg.cmp == NULL) ? default_compare : arg.cmp;
  sort_fn_t sort = (arg.sort == NULL) ? bubble_sort : sorts_callbacks[arg.sort];

  UC_ASSERT(arg.container && "Invalid argument: container");
  UC_ASSERT(compare && "Invalid argument: compare");

  size_t size = container_size(arg.container);
  size_t esize = container_esize(arg.container);
  UC_ASSERT(esize != 0 && "Size of single element can`t be equal 0!");

  if (size == 0)
  {
    return true;
  }

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  size_t arr_size = esize * size;

  void *arr = (void *)mem_allocate(arr_size);
  if (NULL == arr)
  {
    return false;
  }

  bool status1 = uc_to_array(arg.container, arr, arr_size);
  if (!status1)
  {
    mem_free(arr);
    return false;
  }

  sort(arr, arr_size, esize, compare, arg.order);

  container_clear(arg.container);
  bool status = uc_from_array(arg.container, arr, arr_size);

  mem_free(arr);
  return status;
}
