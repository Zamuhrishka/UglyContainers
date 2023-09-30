/**
 * @file    test_Alg_Transformation_UnitTest1.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Unit tests for the `equal` function of the container library.
 * @date 2023-09-27
 *
 * This file contains a suite of tests specifically designed to validate the
 * correctness and robustness of the `equal` function in the container library.
 * The tests cover various scenarios including:
 *   - Size mismatches between containers.
 *   - Element size mismatches.
 *   - Handling of empty containers.
 *   - Failure scenarios related to memory allocation and array transformation.
 *   - Behavior when using different compare functions.
 *
 * These tests are written using the Ceedling test framework and are intended to
 * provide assurance that the `equal` function behaves as expected in both
 * normal and edge-case scenarios.
 *
 * Note: Always ensure you've set up the necessary environment for Ceedling
 * before running these tests.
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "algorithms/equal/uc_equal.h"

// stubs
#include "compare_stub.h"
#include "mem_alloc_stub.h"

// mock
#include "mock_allocator_if.h"
#include "mock_container.h"
#include "mock_uc_transformation.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
container_t container1 = 10;
container_t container2 = 10;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * @brief Tests if the `equal` function can correctly identify containers with different sizes.
 */
void test_UnitTest_1(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: The size container are not equal");

  container_size_ExpectAnyArgsAndReturn(2);
  container_size_ExpectAnyArgsAndReturn(3);

  container_esize_ExpectAnyArgsAndReturn(4);
  container_esize_ExpectAnyArgsAndReturn(4);

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Tests if the `equal` function can correctly identify containers with different element sizes.
 */
void test_UnitTest_2(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: The esize container are not equal");

  container_size_ExpectAnyArgsAndReturn(2);
  container_size_ExpectAnyArgsAndReturn(2);

  container_esize_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(4);

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Tests the behavior of the `equal` function when both containers have a size of 0.
 */
void test_UnitTest_3(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: The size container are 0");

  container_size_ExpectAnyArgsAndReturn(0);
  container_size_ExpectAnyArgsAndReturn(0);

  container_esize_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(2);

  TEST_ASSERT_TRUE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Tests the `equal` function's behavior when there's an internal memory allocation failure.
 */
void test_UnitTest_4(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: inner array fault allocation");

  container_size_ExpectAnyArgsAndReturn(2);
  container_size_ExpectAnyArgsAndReturn(2);

  container_esize_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(2);

  get_allocator_ExpectAndReturn(mem_allocate_fault);

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Tests the `equal` function's behavior when the first `uc_to_array` function fails.
 */
void test_UnitTest_5(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: First `uc_to_array` function fault");

  container_size_ExpectAnyArgsAndReturn(2);
  container_size_ExpectAnyArgsAndReturn(2);

  container_esize_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(2);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  uc_to_array_ExpectAnyArgsAndReturn(false);
  uc_to_array_ExpectAnyArgsAndReturn(true);

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Tests the `equal` function's behavior when the second `uc_to_array` function fails.
 */
void test_UnitTest_6(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: Second `uc_to_array` function fault");

  container_size_ExpectAnyArgsAndReturn(2);
  container_size_ExpectAnyArgsAndReturn(2);

  container_esize_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(2);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  uc_to_array_ExpectAnyArgsAndReturn(true);
  uc_to_array_ExpectAnyArgsAndReturn(false);

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Tests the `equal` function's behavior when provided a compare function that always returns `false`.
 */
void test_UnitTest_7(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: Inner compare function return `false`");

  container_size_ExpectAnyArgsAndReturn(2);
  container_size_ExpectAnyArgsAndReturn(2);

  container_esize_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(2);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  uc_to_array_ExpectAnyArgsAndReturn(true);
  uc_to_array_ExpectAnyArgsAndReturn(true);

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2, .cmp = compare_false));
}

/**
 * @brief Tests the `equal` function's behavior under normal conditions where everything is expected to succeed.
 */
void test_UnitTest_8(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_equal_base`: All goes fine");

  container_size_ExpectAnyArgsAndReturn(2);
  container_size_ExpectAnyArgsAndReturn(2);

  container_esize_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(2);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  uc_to_array_ExpectAnyArgsAndReturn(true);
  uc_to_array_ExpectAnyArgsAndReturn(true);

  TEST_ASSERT_TRUE(uc_equal(.container1 = container1, .container2 = container2, .cmp = compare_true));
}
