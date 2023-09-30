//==============================================================================
// !!!!!!!!!!!!!!!!!!!!!!!!!!! IN DEVELOPMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//==============================================================================
#if 0
/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

//_____ I N C L U D E S _______________________________________________________
  #include "msc.h"

  #include "common/contants.h"
  #include "common/uc_assert.h"
  #include "core/container.h"
  #include "interface/allocator_if.h"

  #include "algorithms/iterator/iterator.h"
  #include "algorithms/sort/sort.h"
  #include "algorithms/transformation/uc_transformation.h"
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
bool unique(container_t *container)
{
  size_t size = container_size(container);
  size_t esize = container_esize(container);

  uc_sort(.container = container);
  int j = 0;

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  size_t arr_size = esize * size;

  void *arr = (void *)mem_allocate(arr_size);
  if (NULL == arr)
  {
    return false;
  }

  bool status1 = uc_to_array(container, arr, arr_size);
  if (!status1)
  {
    mem_free(arr);
    return false;
  }

  for (size_t i = 0; i < size - esize; i = i + esize)
  {
    void *data_i = ((uint8_t *)arr + i);
    void *data_ii = ((uint8_t *)arr + i + esize);

    void *data_j = NULL;
    if (!compare(data_i, data_ii, esize))
    {
      data_j = ((uint8_t *)arr + j + esize);
      memcpy(data_j, data_i, esize);
    }
  }

  void *data_n = ((uint8_t *)arr + n - esize);
  memcpy(data_j, data_n, esize);

  container_clear(container);
  uc_from_array(container, arr, arr_size);

  mem_free(arr);
  return true;
}

// int removeDuplicates(int arr[], int n) {
//     if (n == 0 || n == 1) {
//         return n;
//     }

//     qsort(arr, n, sizeof(int), compare); // Сортировка массива

//     int j = 0; // Индекс для следующего уникального элемента
//     for (int i = 0; i < n - 1; i++) {
//         if (arr[i] != arr[i + 1]) {
//             arr[j++] = arr[i];
//         }
//     }
//     arr[j++] = arr[n - 1];

//     return j; // Новый размер массива
// }

container_t *reverse(container_t *container) {}

//---------------------------------------------------------------------------------------------------

void *search(container_t *container, bool (*match)(void *value)) {}

bool fill(container_t *container, size_t start, size_t end, void *value) {}
bool slice(container_t *container, size_t start, size_t end, void *value) {}
#endif
