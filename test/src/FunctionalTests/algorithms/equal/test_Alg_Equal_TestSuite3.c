/**
 * @file    test_Alg_Equal_TestSuite3.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Tests for the 'equal' function for containers based on linked list ans stores `uint32_t` data.
 *
 * This file contains a series of tests to verify the correctness of the 'equal' function,
 * which is responsible for comparing two containers. The tests cover various scenarios, including:
 * - Comparing two empty containers.
 * - Comparing one empty and one full container.
 * - Comparing two equal full containers.
 * - Comparing two different full containers.
 *
 * Each test case is designed to ensure that the 'equal' function behaves as expected
 * in different situations, correctly identifying whether containers are equal or not.
 *
 * @date 2023-09-28
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "algorithms/equal/uc_equal.h"
#include "algorithms/transformation/transformation.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "interface/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
typedef uint32_t element_t;
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static container_t *container1 = NULL;
static container_t *container2 = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  container1 = container_create(sizeof(element_t), CONTAINER_LINKED_LIST_BASED);
  TEST_ASSERT_NOT_NULL(container1);
  container2 = container_create(sizeof(element_t), CONTAINER_LINKED_LIST_BASED);
  TEST_ASSERT_NOT_NULL(container2);
}

void tearDown(void)
{
  container_delete(&container1);
  container_delete(&container2);
}

/**
 * @brief Test for the 'equal' function with empty containers stores `uint32_t` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing two empty containers. It tests whether the 'equal' function
 * correctly identifies that two empty containers are equal and returns true.
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with empty linked list containers stores `uint32_t` data");

  TEST_ASSERT_TRUE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with one empty and one full container stores `uint32_t` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing one empty container (container2) and one container (container1)
 * filled with elements. It tests whether the 'equal' function correctly identifies
 * that these containers are not equal and returns false.
 */
void test_TestCase_1(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list  container stores `uint32_t` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container1, &input[i]);
  }

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with one empty and one full container stores `uint32_t` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing one empty container (container1) and one container (container2)
 * filled with elements. It tests whether the 'equal' function correctly identifies
 * that these containers are not equal and returns false.
 */
void test_TestCase_2(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list container stores `uint32_t` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container2, &input[i]);
  }

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with two equal full containers stores `uint32_t` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing two equal containers, both filled with the same set of elements.
 * It tests whether the 'equal' function correctly identifies that these containers
 * are equal and returns true.
 */
void test_TestCase_3(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with two equal full linked list containers stores `uint32_t` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container1, &input[i]);
    container_push_back(container2, &input[i]);
  }

  TEST_ASSERT_TRUE(uc_equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with two different full containers stores `uint32_t` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing two different containers, both filled with elements. It tests
 * whether the 'equal' function correctly identifies that these containers are
 * not equal and returns false.
 */
void test_TestCase_4(void)
{
  element_t input1[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t input2[] = {93, 111, 67, 33, 66, 99, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with two different full linked list containers stores `uint32_t` data");

  for (size_t i = 0; i < sizeof(input1) / sizeof(element_t); i++)
  {
    container_push_back(container1, &input1[i]);
  }

  for (size_t i = 0; i < sizeof(input2) / sizeof(element_t); i++)
  {
    container_push_back(container2, &input2[i]);
  }

  TEST_ASSERT_FALSE(uc_equal(.container1 = container1, .container2 = container2));
}
