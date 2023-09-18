/**
 * @file    test_container_TestSuite1.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Linked List based Container. This list of tests just
 *          checks that all linked list methods are executes but not checks the
 *          valid execution.
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "container.h"
#include "interface/allocator_if.h"
#include "linked_list.h"
#include "vector.h"

//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
container_t* container = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  container = container_create(sizeof(uint8_t), CONTAINER_LINKED_LIST_BASED);
}

void tearDown(void)
{
  container_delete((container_t**)container);
}

void test_init(void)
{
  TEST_MESSAGE("Container Linked List Simple Tests");
}

/**
 * \brief Test case to verify linked list creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[CONTAINER_TEST]: create");
  TEST_ASSERT_NOT_NULL(container);
}

/**
 * @brief The unit test verifies the push front linked list`s method.
 */
void test_TestCase_1(void)
{
  uint8_t input = 0x55;
  TEST_MESSAGE("[CONTAINER_TEST]: push front");
  TEST_ASSERT_TRUE(container_push_front(container, &input));
}

/**
 * @brief The unit test verifies the pop front linked list`s method.
 */
void test_TestCase_2(void)
{
  uint8_t output = 0;
  uint8_t input = 0x55;

  TEST_MESSAGE("[CONTAINER_TEST]: pop front");

  container_push_front(container, &input);

  TEST_ASSERT_TRUE(container_pop_front(container, &output));
  TEST_ASSERT_EQUAL_UINT8(input, output);
}

/**
 * @brief The unit test verifies the push back linked list`s method.
 */
void test_TestCase_3(void)
{
  uint8_t input = 0x55;
  TEST_MESSAGE("[CONTAINER_TEST]: push back");
  TEST_ASSERT_TRUE(container_push_back(container, &input));
}

/**
 * @brief The unit test verifies the pop back linked list`s method.
 */
void test_TestCase_4(void)
{
  uint8_t output = 0;
  uint8_t input = 0x55;

  TEST_MESSAGE("[CONTAINER_TEST]: pop back");

  container_push_back(container, &input);

  TEST_ASSERT_TRUE(container_pop_back(container, &output));
  TEST_ASSERT_EQUAL_UINT32(input, output);
}

/**
 * @brief The unit test verifies the insert linked list`s method.
 */
void test_TestCase_5(void)
{
  uint8_t input = 0x55;
  TEST_MESSAGE("[CONTAINER_TEST]: insert");
  TEST_ASSERT_TRUE(container_insert(container, &input, 0));
  TEST_ASSERT_TRUE(container_insert(container, &input, 0));
}

/**
 * @brief The unit test verifies the at linked list`s method.
 */
void test_TestCase_6(void)
{
  uint8_t input = 0x55;
  uint8_t output = 0;

  TEST_MESSAGE("[CONTAINER_TEST]: at");

  container_insert(container, &input, 0);

  TEST_ASSERT_TRUE(container_at(container, &output, 0));
  TEST_ASSERT_EQUAL_UINT32(input, output);
}

/**
 * @brief The unit test verifies the erase linked list`s method.
 */
void test_TestCase_7(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[CONTAINER_TEST]: erase");

  container_insert(container, &input, 0);

  TEST_ASSERT_TRUE(container_erase(container, 0));
}

/**
 * @brief The unit test verifies the size linked list`s method.
 */
void test_TestCase_8(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[CONTAINER_TEST]: size");

  container_push_front(container, &input);

  size_t size = container_size(container);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

/**
 * @brief The unit test verifies the extract linked list`s method.
 */
void test_TestCase_9(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[CONTAINER_TEST]: extract");

  container_insert(container, &input, 0);

  TEST_ASSERT_TRUE(container_extract(container, &input, 0));
}

/**
 * @brief The unit test verifies the replace linked list`s method.
 */
void test_TestCase_10(void)
{
  uint8_t input = 0x55;
  uint8_t output = 0;

  TEST_MESSAGE("[CONTAINER_TEST]: replace");

  container_insert(container, &input, 0);

  input++;
  TEST_ASSERT_TRUE(container_replace(container, &input, 0));
  TEST_ASSERT_TRUE(container_at(container, &output, 0));
  TEST_ASSERT_EQUAL_UINT8(output, input);
}

/**
 * @brief The unit test verifies the clear linked list`s method.
 */
void test_TestCase_11(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[CONTAINER_TEST]: clear");

  container_insert(container, &input, 0);

  size_t size = container_size(container);
  TEST_ASSERT_EQUAL_UINT8(1, size);
  TEST_ASSERT_TRUE(container_clear(container));
  size = container_size(container);
  TEST_ASSERT_EQUAL_UINT8(0, size);
}

/**
 * @brief The unit test verifies the peek linked list`s method.
 */
void test_TestCase_12(void)
{
  uint8_t input = 0x55;
  uint8_t* output = NULL;

  TEST_MESSAGE("[CONTAINER_TEST]: peek");

  container_insert(container, &input, 0);

  output = (uint8_t*)container_peek(container, 0);
  TEST_ASSERT_TRUE(output);
  TEST_ASSERT_EQUAL_UINT8(input, *output);
}

/**
 * @brief The unit test verifies the resize linked list`s method.
 */
void test_TestCase_13(void)
{
  TEST_MESSAGE("[CONTAINER_TEST]: resize");
  TEST_ASSERT_TRUE(container_resize(container, 10));
}
