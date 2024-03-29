/**
 * @file    test_linkedlist_TestSuite1.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Linked List 8-bit data. This list of tests just
 *          checks that all linked list methods are executes but not checks the
 *          valid execution.
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "interface/allocator_if.h"
#include "linked_list.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static linked_list_t* ll = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  ll = linked_list_create(sizeof(uint8_t));
}

void tearDown(void)
{
  linked_list_delete(&ll);
}

void test_init(void)
{
  TEST_MESSAGE("Linked List Simple Tests For 8-bit Data");
}

/**
 * \brief Test case to verify creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[LL_TEST]: create");
  TEST_ASSERT_NOT_NULL(ll);
}

/**
 * @brief The unit test verifies the push front method.
 */
void test_TestCase_1(void)
{
  uint8_t input = 0x55;
  TEST_MESSAGE("[LL_TEST]: push front");
  TEST_ASSERT_TRUE(ll->push_front(ll, &input));
}

/**
 * @brief The unit test verifies the pop front method.
 */
void test_TestCase_2(void)
{
  uint8_t output = 0;
  uint8_t input = 0x55;

  TEST_MESSAGE("[LL_TEST]: pop front");

  ll->push_front(ll, &input);

  TEST_ASSERT_TRUE(ll->pop_front(ll, &output));
  TEST_ASSERT_EQUAL_UINT32(input, output);
}

/**
 * @brief The unit test verifies the push back method.
 */
void test_TestCase_3(void)
{
  uint8_t input = 0x55;
  TEST_MESSAGE("[LL_TEST]: push back");
  TEST_ASSERT_TRUE(ll->push_back(ll, &input));
}

/**
 * @brief The unit test verifies the pop back method.
 */
void test_TestCase_4(void)
{
  uint8_t output = 0;
  uint8_t input = 0x55;

  TEST_MESSAGE("[LL_TEST]: pop back");

  ll->push_back(ll, &input);

  TEST_ASSERT_TRUE(ll->pop_back(ll, &output));
  TEST_ASSERT_EQUAL_UINT32(input, output);
}

/**
 * @brief The unit test verifies the insert method.
 */
void test_TestCase_5(void)
{
  uint8_t input = 0x55;
  TEST_MESSAGE("[LL_TEST]: insert");
  TEST_ASSERT_TRUE(ll->insert(ll, &input, 0));
  TEST_ASSERT_TRUE(ll->insert(ll, &input, 0));
}

/**
 * @brief The unit test verifies the at method.
 */
void test_TestCase_6(void)
{
  uint8_t input = 0x55;
  uint8_t output = 0;

  TEST_MESSAGE("[LL_TEST]: at");

  ll->insert(ll, &input, 0);

  TEST_ASSERT_TRUE(ll->at(ll, &output, 0));
  TEST_ASSERT_EQUAL_UINT32(input, output);
}

/**
 * @brief The unit test verifies the erase method.
 */
void test_TestCase_7(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[LL_TEST]: erase");

  ll->insert(ll, &input, 0);

  TEST_ASSERT_TRUE(ll->erase(ll, 0));
}

/**
 * @brief The unit test verifies the size method.
 */
void test_TestCase_8(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[LL_TEST]: size");

  ll->push_front(ll, &input);

  size_t size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

/**
 * @brief The unit test verifies the extract method.
 */
void test_TestCase_9(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[LL_TEST]: extract");

  ll->insert(ll, &input, 0);

  TEST_ASSERT_TRUE(ll->extract(ll, &input, 0));
}

/**
 * @brief The unit test verifies the replace method.
 */
void test_TestCase_10(void)
{
  uint8_t input = 0x55;
  uint8_t output = 0;

  TEST_MESSAGE("[LL_TEST]: replace");

  ll->insert(ll, &input, 0);

  input++;
  TEST_ASSERT_TRUE(ll->replace(ll, &input, 0));
  TEST_ASSERT_TRUE(ll->at(ll, &output, 0));
  TEST_ASSERT_EQUAL_UINT8(output, input);
}

/**
 * @brief The unit test verifies the clear method.
 */
void test_TestCase_11(void)
{
  uint8_t input = 0x55;

  TEST_MESSAGE("[LL_TEST]: clear");

  ll->insert(ll, &input, 0);

  size_t size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT8(1, size);
  TEST_ASSERT_TRUE(ll->clear(ll));
  size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT8(0, size);
}

/**
 * @brief The unit test verifies the peek method.
 */
void test_TestCase_12(void)
{
  uint8_t input = 0x55;
  uint8_t* output = NULL;

  TEST_MESSAGE("[LL_TEST]: peek");

  ll->insert(ll, &input, 0);

  output = (uint8_t*)ll->peek(ll, 0);
  TEST_ASSERT_TRUE(output);
  TEST_ASSERT_EQUAL_UINT8(input, *output);
}

/**
 * @brief The unit test verifies the resize method.
 */
void test_TestCase_13(void)
{
  TEST_MESSAGE("[LL_TEST]: resize");
  TEST_ASSERT_TRUE(ll->resize(ll, 10));
}
