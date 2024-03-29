/**
 * @file    test_linkedlist_TestSuite7.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Linked List 8-bit data. This list of tests
 *          checks that all linked list methods are correct executes i.e. works with
 *          data as expected.
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
static linked_list_t *ll = NULL;
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
  TEST_MESSAGE("Linked List Complex Tests For 8-bit Data");
}

/**
 * \brief Test case to verify linked list creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[LL_TEST]: Create");
  TEST_ASSERT_NOT_NULL(ll);
}

/**
 * @brief The unit test verifies that method `pop front` reads valid data after `push front`.
 */
void test_TestCase_1(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[] = {1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: push front/pop front");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->pop_front(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `pop back` reads valid data after `push back`.
 */
void test_TestCase_2(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[] = {1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: push back/pop back");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->pop_back(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `pop back` reads valid data after `push front`.
 */
void test_TestCase_3(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: push front/pop back");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->pop_back(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `pop front` reads valid data after `push back`.
 */
void test_TestCase_4(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: push back/pop front");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->pop_front(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `at` reads valid data.
 */
void test_TestCase_5(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: at");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->at(ll, &output[i], i));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `insert` add data valid data into linked list.
 */
void test_TestCase_6(void)
{
  uint8_t input[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: insert #1");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->insert(ll, &input[i], i));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `insert` add data in valid positions.
 */
void test_TestCase_7(void)
{
  uint8_t input[] = {1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t expected[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: insert #2");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
  }

  uint8_t values[] = {11, 33, 55, 77, 99};
  TEST_ASSERT_TRUE(ll->insert(ll, &values[0], 1));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[1], 3));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[2], 5));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[3], 7));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[4], 9));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `extract` read valid data.
 */
void test_TestCase_8(void)
{
  uint8_t input[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};
  uint8_t values[] = {11, 33, 55, 77, 99};
  uint8_t extracted[sizeof(values) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: extract");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[0], 1));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[1], 2));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[2], 3));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[3], 4));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[4], 5));

  TEST_ASSERT_EQUAL_UINT8_ARRAY(values, extracted, sizeof(values) / sizeof(uint8_t));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `replace` replace valid data for valid positions.
 */
void test_TestCase_9(void)
{
  uint8_t input[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {11, 11, 33, 33, 55, 55, 77, 77, 99, 99, 100, 90, 90, 56, 1};
  uint8_t values[] = {11, 33, 55, 77, 99};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: replace");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  TEST_ASSERT_TRUE(ll->replace(ll, &values[0], 0));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[1], 2));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[2], 4));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[3], 6));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[4], 8));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `erase` remove valid data in valid positions.
 */
void test_TestCase_10(void)
{
  uint8_t input[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: erase");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  TEST_ASSERT_TRUE(ll->erase(ll, 1));
  TEST_ASSERT_TRUE(ll->erase(ll, 2));
  TEST_ASSERT_TRUE(ll->erase(ll, 3));
  TEST_ASSERT_TRUE(ll->erase(ll, 4));
  TEST_ASSERT_TRUE(ll->erase(ll, 5));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `size` return valid size after `push front` method.
 */
void test_TestCase_11(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(input) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: size #1");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    ll->push_front(ll, &input[i]);
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(sizeof(output) / sizeof(uint8_t) - i, size);
    ll->pop_front(ll, &output[i]);
  }
}

/**
 * @brief The unit test verifies that method `size` return valid size after `push back` method.
 */
void test_TestCase_12(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(input) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: size #2");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    ll->push_back(ll, &input[i]);
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(sizeof(output) / sizeof(uint8_t) - i, size);
    ll->pop_back(ll, &output[i]);
  }
}

void test_TestCase_13(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(input) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: size #3");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    ll->push_front(ll, &input[i]);
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(sizeof(output) / sizeof(uint8_t) - i, size);
    ll->pop_back(ll, &output[i]);
  }
}

void test_TestCase_14(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(input) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: size #4");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    ll->push_back(ll, &input[i]);
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(sizeof(output) / sizeof(uint8_t) - i, size);
    ll->pop_front(ll, &output[i]);
  }
}

void test_TestCase_15(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(input) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: size #5");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    ll->push_back(ll, &input[i]);
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(sizeof(output) / sizeof(uint8_t), size);
    ll->at(ll, &output[i], i);
  }
}

void test_TestCase_16(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[LL_TEST]: size #6");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    ll->insert(ll, &input[i], i);
  }
}

void test_TestCase_17(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[LL_TEST]: size #7");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(sizeof(input) / sizeof(uint8_t) - i, size);
    ll->erase(ll, 0);
  }
}

void test_TestCase_18(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output = 0;

  TEST_MESSAGE("[LL_TEST]: size #8");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT8(sizeof(input) / sizeof(uint8_t) - i, size);
    ll->extract(ll, &output, 0);
  }
}

/**
 * @brief The unit test verifies that method `clear` works as expected.
 */
void test_TestCase_19(void)
{
  uint8_t input[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 11, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: clear");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  size_t size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT8(sizeof(expected) / sizeof(uint8_t), size);
  TEST_ASSERT_TRUE(ll->clear(ll));
  size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT8(0, size);

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->insert(ll, &input[i], i));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief The unit test verifies that method `peek` return valid data in valid positions.
 */
void test_TestCase_20(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[LL_TEST]: peek");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    uint8_t *out = ll->peek(ll, i);
    TEST_ASSERT_TRUE(out);
    output[i] = *out;
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}
