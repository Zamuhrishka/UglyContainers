/**
 * @file    test_Alg_Transformation_UnitTest1.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Unit tests for the `uc_sort_base` function of the container library.
 * @date 2023-09-27
 *
 * This file contains a suite of tests specifically designed to validate the
 * correctness and robustness of the `uc_sort_base` function in the container library.
 *
 * These tests are written using the Ceedling test framework and are intended to
 * provide assurance that the `uc_sort_base` function behaves as expected in both
 * normal and edge-case scenarios.
 *
 * Note: Always ensure you've set up the necessary environment for Ceedling
 * before running these tests.
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "algorithms/sort/uc_sort.h"

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
container_t container = 10;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void test_UnitTest_1(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_sort_base`: The size container are zero");

  container_size_ExpectAnyArgsAndReturn(0);
  container_esize_ExpectAnyArgsAndReturn(4);

  TEST_ASSERT_TRUE(uc_sort(.container = container));
}

void test_UnitTest_2(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_sort_base`: Fault of allocation array");

  container_size_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(4);

  get_allocator_ExpectAndReturn(mem_allocate_fault);
  get_free_ExpectAndReturn(mem_free);

  TEST_ASSERT_FALSE(uc_sort(.container = container));
}

void test_UnitTest_3(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_sort_base`: Fault of copy data from container to array");

  container_size_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(4);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  uc_to_array_ExpectAnyArgsAndReturn(false);

  TEST_ASSERT_FALSE(uc_sort(.container = container));
}

void test_UnitTest_4(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_sort_base`: Fault of copy sorted data from array back to container");

  container_size_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(4);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  uc_to_array_ExpectAnyArgsAndReturn(true);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  container_clear_ExpectAnyArgsAndReturn(2);
  uc_from_array_ExpectAnyArgsAndReturn(false);

  TEST_ASSERT_FALSE(uc_sort(.container = container));
}

void test_UnitTest_5(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  TEST_MESSAGE("Testing `uc_sort_base`: All goes well");

  container_size_ExpectAnyArgsAndReturn(2);
  container_esize_ExpectAnyArgsAndReturn(4);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  uc_to_array_ExpectAnyArgsAndReturn(true);

  get_allocator_ExpectAndReturn(mem_allocate);
  get_free_ExpectAndReturn(mem_free);

  container_clear_ExpectAnyArgsAndReturn(2);
  uc_from_array_ExpectAnyArgsAndReturn(true);

  TEST_ASSERT_TRUE(uc_sort(.container = container));
}
