/**
 * @file    test_Alg_Equal_TestSuite3.c
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Tests for the 'equal' function for containers based on linked list ans stores `structure` data.
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

#include "algorithms/equal/equal.h"
#include "algorithms/transformation/transformation.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "interface/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
typedef struct
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
} element_t;
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
 * @brief Test for the 'equal' function with empty containers stores `structure` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing two empty containers. It tests whether the 'equal' function
 * correctly identifies that two empty containers are equal and returns true.
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with empty linked list containers stores `structure` data");

  TEST_ASSERT_TRUE(equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with one empty and one full container stores `structure` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing one empty container (container2) and one container (container1)
 * filled with elements. It tests whether the 'equal' function correctly identifies
 * that these containers are not equal and returns false.
 */
void test_TestCase_1(void)
{
  element_t input[] = {
    {.a = 0x93939393, .b = 0x9393, .c = 0x93},
    {.a = 0x67676767, .b = 0x6767, .c = 0x67},
    {.a = 0x66666666, .b = 0x6666, .c = 0x66},
    {.a = 0x54545454, .b = 0x5454, .c = 0x54},
    {.a = 0x77777777, .b = 0x7777, .c = 0x77},
    {.a = 0xAAAAAAAA, .b = 0xAAAA, .c = 0xAA},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x56565656, .b = 0x5656, .c = 0x56},
    {.a = 0x11111111, .b = 0x1111, .c = 0x11},
  };

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list  container stores `structure` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container1, &input[i]);
  }

  TEST_ASSERT_FALSE(equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with one empty and one full container stores `structure` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing one empty container (container1) and one container (container2)
 * filled with elements. It tests whether the 'equal' function correctly identifies
 * that these containers are not equal and returns false.
 */
void test_TestCase_2(void)
{
  element_t input[] = {
    {.a = 0x93939393, .b = 0x9393, .c = 0x93},
    {.a = 0x67676767, .b = 0x6767, .c = 0x67},
    {.a = 0x66666666, .b = 0x6666, .c = 0x66},
    {.a = 0x54545454, .b = 0x5454, .c = 0x54},
    {.a = 0x77777777, .b = 0x7777, .c = 0x77},
    {.a = 0xAAAAAAAA, .b = 0xAAAA, .c = 0xAA},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x56565656, .b = 0x5656, .c = 0x56},
    {.a = 0x11111111, .b = 0x1111, .c = 0x11},
  };

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with one empty and one full linked list container stores `structure` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container2, &input[i]);
  }

  TEST_ASSERT_FALSE(equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with two equal full containers stores `structure` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing two equal containers, both filled with the same set of elements.
 * It tests whether the 'equal' function correctly identifies that these containers
 * are equal and returns true.
 */
void test_TestCase_3(void)
{
  element_t input[] = {
    {.a = 0x93939393, .b = 0x9393, .c = 0x93},
    {.a = 0x67676767, .b = 0x6767, .c = 0x67},
    {.a = 0x66666666, .b = 0x6666, .c = 0x66},
    {.a = 0x54545454, .b = 0x5454, .c = 0x54},
    {.a = 0x77777777, .b = 0x7777, .c = 0x77},
    {.a = 0xAAAAAAAA, .b = 0xAAAA, .c = 0xAA},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x56565656, .b = 0x5656, .c = 0x56},
    {.a = 0x11111111, .b = 0x1111, .c = 0x11},
  };

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with two equal full linked list containers stores `structure` data");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container1, &input[i]);
    container_push_back(container2, &input[i]);
  }

  TEST_ASSERT_TRUE(equal(.container1 = container1, .container2 = container2));
}

/**
 * @brief Test for the 'equal' function with two different full containers stores `structure` data.
 *
 * This test case is designed to verify the behavior of the 'equal' function
 * when comparing two different containers, both filled with elements. It tests
 * whether the 'equal' function correctly identifies that these containers are
 * not equal and returns false.
 */
void test_TestCase_4(void)
{
  element_t input1[] = {
    {.a = 0x93939393, .b = 0x9393, .c = 0x93},
    {.a = 0x67676767, .b = 0x6767, .c = 0x67},
    {.a = 0x66666666, .b = 0x6666, .c = 0x66},
    {.a = 0x54545454, .b = 0x5454, .c = 0x54},
    {.a = 0x77777777, .b = 0x7777, .c = 0x77},
    {.a = 0xAAAAAAAA, .b = 0xAAAA, .c = 0xAA},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x90909090, .b = 0x9090, .c = 0x90},
    {.a = 0x56565656, .b = 0x5656, .c = 0x56},
    {.a = 0x11111111, .b = 0x1111, .c = 0x11},
  };
  element_t input2[] = {
    {.a = 0x93939393, .b = 0x9393, .c = 0x93},
    {.a = 0x67676767, .b = 0x6767, .c = 0x67},
    {.a = 0x66666666, .b = 0x6666, .c = 0x66},
    {.a = 0x56565656, .b = 0x5656, .c = 0x56},
    {.a = 0x11111111, .b = 0x1111, .c = 0x11},
  };

  TEST_MESSAGE("[EQUAL]: Test for the 'equal' function with two different full linked list containers stores `structure` data");

  for (size_t i = 0; i < sizeof(input1) / sizeof(element_t); i++)
  {
    container_push_back(container1, &input1[i]);
  }

  for (size_t i = 0; i < sizeof(input2) / sizeof(element_t); i++)
  {
    container_push_back(container2, &input2[i]);
  }

  TEST_ASSERT_FALSE(equal(.container1 = container1, .container2 = container2));
}
