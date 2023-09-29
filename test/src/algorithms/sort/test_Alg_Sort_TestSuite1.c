//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "interface/allocator_if.h"

#include "algorithms/sort/uc_sort.h"
#include "algorithms/transformation/transformation.h"
//_____ C O N F I G S  ________________________________________________________
typedef uint32_t element_t;
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static container_t *container = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  container = container_create(sizeof(element_t), CONTAINER_LINKED_LIST_BASED);
  TEST_ASSERT_NOT_NULL(container);
}

void tearDown(void)
{
  container_delete(&container);
}

void test_TestCase_0(void)
{
  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with empty linked list containers stores `uint8_t` data");

  TEST_ASSERT_TRUE(uc_sort(.container = container));
}

void test_TestCase_1(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t expected[] = {1, 33, 54, 55, 56, 66, 67, 77, 77, 90, 90, 93, 99, 100, 111};
  element_t output[sizeof(expected) / sizeof(element_t)] = {};
  size_t arr_size = sizeof(expected) / sizeof(element_t);

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list  container stores `uint8_t` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container, &input[i]);
  }

  TEST_ASSERT_TRUE(uc_sort(.container = container));

  to_array(container, output, arr_size);

  /* Checking that data in container is valid */
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, arr_size);
}

void test_TestCase_2(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t expected[] = {1, 33, 54, 55, 56, 66, 67, 77, 77, 90, 90, 93, 99, 100, 111};
  element_t output[sizeof(expected) / sizeof(element_t)] = {};
  size_t arr_size = sizeof(expected) / sizeof(element_t);

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list  container stores `uint8_t` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container, &input[i]);
  }

  TEST_ASSERT_TRUE(uc_sort(.container = container, .sort = UC_SELECTION_SORT));

  to_array(container, output, arr_size);

  /* Checking that data in container is valid */
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, arr_size);
}

void test_TestCase_3(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t expected[] = {111, 100, 99, 93, 90, 90, 77, 77, 67, 66, 56, 55, 54, 33, 1};
  element_t output[sizeof(expected) / sizeof(element_t)] = {};
  size_t arr_size = sizeof(expected) / sizeof(element_t);

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list  container stores `uint8_t` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container, &input[i]);
  }

  TEST_ASSERT_TRUE(uc_sort(.container = container, .order = SORT_DESCENDING));

  to_array(container, output, arr_size);

  /* Checking that data in container is valid */
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, arr_size);
}

void test_TestCase_4(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t expected[] = {111, 100, 99, 93, 90, 90, 77, 77, 67, 66, 56, 55, 54, 33, 1};
  element_t output[sizeof(expected) / sizeof(element_t)] = {};
  size_t arr_size = sizeof(expected) / sizeof(element_t);

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list  container stores `uint8_t` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container, &input[i]);
  }

  TEST_ASSERT_TRUE(uc_sort(.container = container, .sort = UC_SELECTION_SORT, .order = SORT_DESCENDING));

  to_array(container, output, arr_size);

  /* Checking that data in container is valid */
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, arr_size);
}
