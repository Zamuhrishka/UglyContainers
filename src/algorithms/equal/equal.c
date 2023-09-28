/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

//_____ I N C L U D E S _______________________________________________________
#include "equal.h"

#include <string.h>

#include "common/contants.h"
#include "common/uc_assert.h"

#include "core/container.h"
#include "interface/allocator_if.h"

#include "algorithms/transformation/transformation.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static bool default_compare(const void *value1, const void *value2, size_t esize)
{
  return 0 == memcmp(value1, value2, esize);
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
bool container_equal(AlgEqualArg_t arg)
{
  bool status = true;
  equal_fn_t compare = (arg.cmp == NULL) ? default_compare : arg.cmp;

  UC_ASSERT(arg.container1 && "Invalid argument: container1");
  UC_ASSERT(arg.container2 && "Invalid argument: container2");

  size_t size1 = container_size(arg.container1);
  size_t size2 = container_size(arg.container2);

  size_t esize1 = container_esize(arg.container1);
  size_t esize2 = container_esize(arg.container2);

  if (size1 != size2 || esize1 != esize2)
  {
    return false;
  }

  if (size1 == 0)
  {
    return true;
  }

  allocate_fn_t mem_allocate = get_allocator();

  void *arr1 = (void *)mem_allocate(esize1 * size1);
  void *arr2 = (void *)mem_allocate(esize2 * size2);
  if (NULL == arr1 || NULL == arr2)
  {
    return false;
  }

  free_fn_t mem_free = get_free();

  size_t arr_size = esize1 * size1;
  bool status1 = to_array(arg.container1, arr1, arr_size);
  bool status2 = to_array(arg.container2, arr2, arr_size);

  if (!(status1 & status2))
  {
    status = false;
    goto exit;
  }

  for (size_t i = 0; i < arr_size; i = i + esize1)
  {
    void *ndata1 = ((uint8_t *)arr1 + i);
    void *ndata2 = ((uint8_t *)arr2 + i);

    if (!compare(ndata1, ndata2, esize1))
    {
      status = false;
      goto exit;
    }
  }

exit:
  mem_free(arr1);
  mem_free(arr2);
  return status;
}
