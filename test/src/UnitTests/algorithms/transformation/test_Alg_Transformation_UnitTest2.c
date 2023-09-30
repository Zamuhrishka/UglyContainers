/**
 * @file    test_Alg_Transformation_UnitTest2.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Unit tests for the array to container transformation functions of the container library.
 *
 * This file contains the unit tests designed to validate the correctness and behavior
 * of the transformation functions, specifically the `uc_from_array` function, under various
 * scenarios. These tests cover standard use cases as well as error conditions,
 * ensuring that the function behaves as expected across different conditions.
 *
 * Scenarios include:
 * - Array and container sizes matching.
 * - Errors and failures from helper functions, especially during data insertion.
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
 * @brief Test for the array to container transformation function with equal sizes.
 *
 * This test evaluates the correctness of the `uc_from_array` function, which
 * transforms an array to a container representation. The function is tested
 * by providing an array of known values. The subsequent insertion of these values
 * into the container is then verified using mocked behaviors for the `container_push_back` function.
 * The test ensures that the `uc_from_array` function is capable of transforming an array
 * into a container when the sizes of both are equal.
 */
void test_UnitTest_0(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_from_array`: Size of container and array are equal");

  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_push_back_ExpectAnyArgsAndReturn(true);
  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_push_back_ExpectAnyArgsAndReturn(true);

  bool status = uc_from_array(&container, output, arr_size);
  TEST_ASSERT_TRUE(status);
}

/**
 * @brief Test for the array to container transformation function when insertion fails.
 *
 * This test evaluates the error handling of the `uc_from_array` function by simulating
 * a scenario where the `container_push_back` function fails (e.g., due to memory allocation
 * issues or other reasons). The test ensures that the `uc_from_array` function correctly
 * identifies and responds to such failures by returning a status of `false`.
 */
void test_UnitTest_1(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_from_array`: The `container_push_back` function fails");

  container_esize_ExpectAnyArgsAndReturn(sizeof(uint32_t));
  container_push_back_ExpectAnyArgsAndReturn(false);

  bool status = uc_from_array(&container, output, arr_size);
  TEST_ASSERT_FALSE(status);
}
