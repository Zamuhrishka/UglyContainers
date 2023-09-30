/**
 * @file    test_Alg_Transformation_UnitTest1.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Unit tests for the transformation functions of the container library.
 *
 * This file contains the unit tests designed to validate the correctness and behavior
 * of the transformation functions, specifically the `uc_to_array` function, under various
 * scenarios. These tests cover standard use cases as well as edge and corner cases,
 * ensuring that the function behaves as expected across different conditions.
 *
 * Scenarios include:
 * - Container and array sizes matching.
 * - Container size being less than the array size.
 * - Container size being greater than the array size.
 * - Errors and failures from helper functions.
 *
 * Each test is self-contained, ensuring that modifications or additions can be made
 * without affecting other tests. Mocks and stubs are used to simulate the behavior of
 * dependent functions and systems.
 *
 * For details on each test's specific purpose and logic, refer to the comments above
 * each test function.
 *
 * @date 2023-09-27
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "algorithms/transformation/transformation.h"
#include "interface/allocator_if.h"

// mock
#include "mock_container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
container_t container = 0;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * @brief Test for the `uc_to_array` function with an empty container.
 *
 * This test evaluates the behavior of the `uc_to_array` function when transforming
 * an empty container to an array representation. The function's expected behavior
 * in this scenario is to return `true` without modifying the output array.
 *
 * The test simulates an empty container by mocking `container_size` to return 0.
 * After invoking the `uc_to_array` function, the test verifies that the function
 * successfully completes without issues.
 */
void test_UnitTest_0(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  // TEST_MESSAGE("[UNIT_TEST:TRANSFORMATION]:");
  // TEST_MESSAGE("                           Func - `uc_to_array`");
  // TEST_MESSAGE("                           Case - Zero size of container");
  TEST_MESSAGE("Testing `uc_to_array` with zero-sized container.");

  container_size_ExpectAnyArgsAndReturn(0);

  bool status = uc_to_array(&container, output, arr_size);
  TEST_ASSERT_TRUE(status);
}

/**
 * @brief Test for the `uc_to_array` function when container and array sizes match.
 *
 * This test evaluates the behavior of the `uc_to_array` function when the container's
 * size is equal to the size of the output array. The expected behavior in this
 * scenario is that all elements from the container should be copied to the output
 * array without any issues.
 */
void test_UnitTest_1(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  // TEST_MESSAGE("[UNIT_TEST:TRANSFORMATION]:");
  // TEST_MESSAGE("                           Func - `uc_to_array`");
  // TEST_MESSAGE("                           Size of container and array are equal");
  TEST_MESSAGE("Testing `uc_to_array`: Size of container matches array size");

  container_size_ExpectAnyArgsAndReturn(2);

  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_at_ExpectAnyArgsAndReturn(true);
  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_at_ExpectAnyArgsAndReturn(true);

  bool status = uc_to_array(&container, output, arr_size);
  TEST_ASSERT_TRUE(status);
}

/**
 * @brief Test for the `uc_to_array` function with container size less than the array size.
 *
 * This test evaluates the behavior of the `uc_to_array` function when the container's
 * size is less than the size of the output array. The function should copy only the
 * available elements from the container to the output array.
 */
void test_UnitTest_2(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_to_array`: Size of container is less than array size");

  container_size_ExpectAnyArgsAndReturn(1);

  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_at_ExpectAnyArgsAndReturn(true);

  bool status = uc_to_array(&container, output, arr_size);
  TEST_ASSERT_TRUE(status);
}

/**
 * @brief Test for the `uc_to_array` function with container size greater than the array size.
 *
 * This test assesses the `uc_to_array` function when the container's size exceeds that
 * of the output array. The function should only copy elements up to the size of the
 * output array and stop once it's full.
 */
void test_UnitTest_3(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_to_array`: Size of container exceeds array size");

  container_size_ExpectAnyArgsAndReturn(3);

  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_at_ExpectAnyArgsAndReturn(true);

  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_at_ExpectAnyArgsAndReturn(true);

  bool status = uc_to_array(&container, output, arr_size);
  TEST_ASSERT_TRUE(status);
}

/**
 * @brief Test for the `uc_to_array` function when `container_at` function fails.
 *
 * This test checks the behavior of the `uc_to_array` function when the `container_at`
 * function (used to access individual container elements) returns `false`. In this
 * case, the `uc_to_array` function should also fail and return `false`.
 */
void test_UnitTest_4(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_to_array`: The `container_at` function fails");

  container_size_ExpectAnyArgsAndReturn(3);

  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_at_ExpectAnyArgsAndReturn(false);

  bool status = uc_to_array(&container, output, arr_size);
  TEST_ASSERT_FALSE(status);
}
