/**
 * @file    test_Alg_Transformation_TestSuite3.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Unit tests for container transformation functions.
 *
 * This file contains functional tests that validate the functionality of converting
 * between container based on Linked List representations and `uint16_t` data arrays.
 * The tests ensure that data integrity is maintained during the transformation processes and
 * that the order of elements remains consistent. It's crucial that any modifications to the
 * transformation functions be reflected in these tests to ensure continued reliability of the
 * library's core functionality.
 *
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "algorithms/transformation/uc_transformation.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "interface/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
typedef uint16_t element_t;
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
container_t *container = NULL;
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

/**
 * @brief Test for the container to array transformation function.
 *
 * This test evaluates the correctness of the `uc_to_array` function which
 * transforms a container to an array representation. The function is tested
 * by populating the container with known values from an input array and
 * then converting it back to an array. The output array is then compared
 * with the expected result.
 */
void test_TestCase_0(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t expected[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t output[sizeof(expected) / sizeof(element_t)] = {};
  size_t arr_size = sizeof(expected) / sizeof(element_t);

  TEST_MESSAGE("[TRANSFORMATION]: Linked list based container to `uint16_t` array transformation test");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container, &input[i]);
  }

  TEST_ASSERT_TRUE(uc_to_array(container, output, arr_size));

  /* Checking that size of container is valid */
  size_t size = container_size(container);
  TEST_ASSERT_EQUAL_UINT16(size, arr_size);

  /* Checking that data in array is valid */
  TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, output, arr_size);
}

/**
 * @brief Test for the array to container transformation and retrieval functions.
 *
 * This test evaluates the correctness of transforming an array into a container
 * and subsequently retrieving its elements. The process is validated by
 * converting a known input array into a container, then retrieving the elements
 * back into an output array. The output is then compared with the original
 * input to ensure data integrity and order preservation.
 */
void test_TestCase_1(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t expected[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t output[sizeof(expected) / sizeof(element_t)] = {};
  size_t arr_size = sizeof(expected) / sizeof(element_t);

  TEST_MESSAGE("[TRANSFORMATION]: Array of `uint16_t` data to linked list based container transformation test");

  TEST_ASSERT_TRUE(uc_from_array(container, input, sizeof(input) / sizeof(element_t)));

  for (size_t i = 0; i < sizeof(output) / sizeof(element_t); i++)
  {
    container_at(container, &output[i], i);
  }

  /* Checking that size of container is valid */
  size_t size = container_size(container);
  TEST_ASSERT_EQUAL_UINT16(size, arr_size);

  /* Checking that data in container is valid */
  TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, output, arr_size);
}
