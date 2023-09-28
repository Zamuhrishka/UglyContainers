/**
 * @file    test_to_array_TestSuite3.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Unit tests for container transformation functions.
 *
 *
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "CException.h"
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "algorithms/transformation/transformation.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "interface/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
typedef uint8_t element_t;
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

void test_TestCase_0(void)
{
  CEXCEPTION_T e;
  element_t output[10] = {};
  size_t arr_size = sizeof(output) / sizeof(element_t);

  TEST_MESSAGE("[TRANSFORMATION]: Corner case -> invalid `container` argument for `to_array` function");

  Try
  {
    bool res = to_array(NULL, output, arr_size);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

void test_TestCase_1(void)
{
  CEXCEPTION_T e;
  size_t arr_size = 10;

  TEST_MESSAGE("[TRANSFORMATION]: Corner case -> invalid `arr` argument for `to_array` function");

  Try
  {
    bool res = to_array(container, NULL, arr_size);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

void test_TestCase_2(void)
{
  CEXCEPTION_T e;
  element_t output[10] = {};

  TEST_MESSAGE("[TRANSFORMATION]: Corner case -> invalid `size` argument for `to_array` function");

  Try
  {
    bool res = to_array(container, output, 0);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

void test_TestCase_3(void)
{
  CEXCEPTION_T e;
  element_t output[10] = {};
  size_t arr_size = sizeof(output) / sizeof(element_t);

  TEST_MESSAGE("[TRANSFORMATION]: Corner case -> invalid `container` argument for `from_array` function");

  Try
  {
    bool res = from_array(NULL, output, arr_size);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

void test_TestCase_4(void)
{
  CEXCEPTION_T e;
  size_t arr_size = 10;

  TEST_MESSAGE("[TRANSFORMATION]: Corner case -> invalid `arr` argument for `from_array` function");

  Try
  {
    bool res = from_array(container, NULL, arr_size);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

void test_TestCase_5(void)
{
  CEXCEPTION_T e;
  element_t output[10] = {};

  TEST_MESSAGE("[TRANSFORMATION]: Corner case -> invalid `size` argument for `from_array` function");

  Try
  {
    bool res = from_array(container, output, 0);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

void test_TestCase_6(void)
{
  element_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  element_t expected[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90};
  element_t output[(sizeof(expected) / sizeof(element_t))] = {};
  size_t arr_size = (sizeof(expected) / sizeof(element_t));

  TEST_MESSAGE("[TRANSFORMATION]: Linked list based container to array transformation test");

  for (size_t i = 0; i < sizeof(input) / sizeof(element_t); i++)
  {
    container_push_back(container, &input[i]);
  }

  TEST_ASSERT_TRUE(to_array(container, output, arr_size));

  /* Checking that size of container is valid */
  size_t size = container_size(container);
  TEST_ASSERT_NOT_EQUAL_UINT8(size, arr_size);

  /* Checking that data in array is valid */
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, arr_size);
}
