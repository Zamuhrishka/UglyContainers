/**
 * @file    test_linkedlist_TestSuite8.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Linked List struct data. This list of tests
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
struct test_ll_simple_struct
{
  uint32_t a;
  uint16_t b;
  uint8_t c;
};
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static linked_list_t* ll = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  ll = linked_list_create(sizeof(struct test_ll_simple_struct));
}

void tearDown(void)
{
  linked_list_delete(&ll);
}

void test_init(void)
{
  TEST_MESSAGE("Linked List Complex Tests For Struct Data");
  TEST_IGNORE_MESSAGE("This TestSuite failed in github action! Need to figure out why.");
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
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 1, .b = 1, .c = 1},    {.a = 56, .b = 56, .c = 56},    {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 100, .b = 100, .c = 100}, {.a = 77, .b = 77, .c = 77},
      {.a = 54, .b = 54, .c = 54}, {.a = 66, .b = 66, .c = 66},    {.a = 67, .b = 67, .c = 67},
      {.a = 93, .b = 93, .c = 93},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(input) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: push front/pop front");

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
  }

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->pop_front(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct), num);
}

/**
 * @brief The unit test verifies that method `pop back` reads valid data after `push back`.
 */
void test_TestCase_2(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 1, .b = 1, .c = 1},    {.a = 56, .b = 56, .c = 56},    {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 100, .b = 100, .c = 100}, {.a = 77, .b = 77, .c = 77},
      {.a = 54, .b = 54, .c = 54}, {.a = 66, .b = 66, .c = 66},    {.a = 67, .b = 67, .c = 67},
      {.a = 93, .b = 93, .c = 93},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(input) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: push back/pop back");

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
  }

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->pop_back(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct), num);
}

/**
 * @brief The unit test verifies that method `pop back` reads valid data after `push front`.
 */
void test_TestCase_3(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(input) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: push front/pop back");

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
  }

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->pop_back(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct), num);
}

/**
 * @brief The unit test verifies that method `pop front` reads valid data after `push back`.
 */
void test_TestCase_4(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(input) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: push back/pop front");

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
  }

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->pop_front(ll, &output[i]));
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct), num);
}

/**
 * @brief The unit test verifies that method `at` reads valid data.
 */
void test_TestCase_5(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(input) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: at");

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
  }

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->at(ll, &output[i], i));
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct), num);
}

/**
 * @brief The unit test verifies that method `insert` add data valid data into linked list.
 */
void test_TestCase_6(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(input) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: insert #1");

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->insert(ll, &input[i], i));
  }

  for (size_t i = 0; i < num; i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct), num);
}

/**
 * @brief The unit test verifies that method `insert` add data in valid positions.
 */
void test_TestCase_7(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 1, .b = 1, .c = 1},    {.a = 56, .b = 56, .c = 56},    {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 100, .b = 100, .c = 100}, {.a = 77, .b = 77, .c = 77},
      {.a = 54, .b = 54, .c = 54}, {.a = 66, .b = 66, .c = 66},    {.a = 67, .b = 67, .c = 67},
      {.a = 93, .b = 93, .c = 93},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 11, .b = 11, .c = 11},    {.a = 67, .b = 67, .c = 67},
      {.a = 33, .b = 33, .c = 33}, {.a = 66, .b = 66, .c = 66},    {.a = 55, .b = 55, .c = 55},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77},    {.a = 77, .b = 77, .c = 77},
      {.a = 99, .b = 99, .c = 99}, {.a = 100, .b = 100, .c = 100}, {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},    {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(input) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: insert #2");

  for (size_t i = 0; i < num; i++)
  {
    TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
  }

  struct test_ll_simple_struct values[] = {{.a = 11, .b = 11, .c = 11},
                                           {.a = 33, .b = 33, .c = 33},
                                           {.a = 55, .b = 55, .c = 55},
                                           {.a = 77, .b = 77, .c = 77},
                                           {.a = 99, .b = 99, .c = 99}};

  TEST_ASSERT_TRUE(ll->insert(ll, &values[0], 1));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[1], 3));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[2], 5));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[3], 7));
  TEST_ASSERT_TRUE(ll->insert(ll, &values[4], 9));

  for (size_t i = 0; i < num; i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct), num);
}

/**
 * @brief The unit test verifies that method `extract` read valid data.
 */
void test_TestCase_8(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 11, .b = 11, .c = 11},    {.a = 67, .b = 67, .c = 67},
      {.a = 33, .b = 33, .c = 33}, {.a = 66, .b = 66, .c = 66},    {.a = 55, .b = 55, .c = 55},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77},    {.a = 77, .b = 77, .c = 77},
      {.a = 99, .b = 99, .c = 99}, {.a = 100, .b = 100, .c = 100}, {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},    {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(expected) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(expected) / sizeof(struct test_ll_simple_struct);

  struct test_ll_simple_struct values[] = {{.a = 11, .b = 11, .c = 11},
                                           {.a = 33, .b = 33, .c = 33},
                                           {.a = 55, .b = 55, .c = 55},
                                           {.a = 77, .b = 77, .c = 77},
                                           {.a = 99, .b = 99, .c = 99}};

  struct test_ll_simple_struct extracted[sizeof(values) / sizeof(struct test_ll_simple_struct)] = {};

  TEST_MESSAGE("[LL_TEST]: extract");

  for (size_t i = 0; i < sizeof(input) / sizeof(struct test_ll_simple_struct); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[0], 1));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[1], 2));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[2], 3));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[3], 4));
  TEST_ASSERT_TRUE(ll->extract(ll, &extracted[4], 5));

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(values, extracted, sizeof(struct test_ll_simple_struct),
                                 sizeof(values) / sizeof(struct test_ll_simple_struct));

  for (size_t i = 0; i < sizeof(expected) / sizeof(struct test_ll_simple_struct); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct),
                                 sizeof(expected) / sizeof(struct test_ll_simple_struct));
}

/**
 * @brief The unit test verifies that method `replace` replace valid data for valid positions.
 */
void test_TestCase_9(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 11, .b = 11, .c = 11},    {.a = 67, .b = 67, .c = 67},
      {.a = 33, .b = 33, .c = 33}, {.a = 66, .b = 66, .c = 66},    {.a = 55, .b = 55, .c = 55},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77},    {.a = 77, .b = 77, .c = 77},
      {.a = 99, .b = 99, .c = 99}, {.a = 100, .b = 100, .c = 100}, {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},    {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 11, .b = 11, .c = 11}, {.a = 11, .b = 11, .c = 11},    {.a = 33, .b = 33, .c = 33},
      {.a = 33, .b = 33, .c = 33}, {.a = 55, .b = 55, .c = 55},    {.a = 55, .b = 55, .c = 55},
      {.a = 77, .b = 77, .c = 77}, {.a = 77, .b = 77, .c = 77},    {.a = 99, .b = 99, .c = 99},
      {.a = 99, .b = 99, .c = 99}, {.a = 100, .b = 100, .c = 100}, {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},    {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct values[] = {{.a = 11, .b = 11, .c = 11},
                                           {.a = 33, .b = 33, .c = 33},
                                           {.a = 55, .b = 55, .c = 55},
                                           {.a = 77, .b = 77, .c = 77},
                                           {.a = 99, .b = 99, .c = 99}};

  struct test_ll_simple_struct output[sizeof(expected) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(expected) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: replace");

  for (size_t i = 0; i < sizeof(input) / sizeof(struct test_ll_simple_struct); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  TEST_ASSERT_TRUE(ll->replace(ll, &values[0], 0));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[1], 2));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[2], 4));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[3], 6));
  TEST_ASSERT_TRUE(ll->replace(ll, &values[4], 8));

  for (size_t i = 0; i < sizeof(expected) / sizeof(struct test_ll_simple_struct); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct),
                                 sizeof(expected) / sizeof(struct test_ll_simple_struct));
}

/**
 * @brief The unit test verifies that method `erase` remove valid data in valid positions.
 */
void test_TestCase_10(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 11, .b = 11, .c = 11},    {.a = 67, .b = 67, .c = 67},
      {.a = 33, .b = 33, .c = 33}, {.a = 66, .b = 66, .c = 66},    {.a = 55, .b = 55, .c = 55},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77},    {.a = 77, .b = 77, .c = 77},
      {.a = 99, .b = 99, .c = 99}, {.a = 100, .b = 100, .c = 100}, {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},    {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct expected[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 67, .b = 67, .c = 67}, {.a = 66, .b = 66, .c = 66},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77}, {.a = 100, .b = 100, .c = 100},
      {.a = 90, .b = 90, .c = 90}, {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},
      {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(expected) / sizeof(struct test_ll_simple_struct)] = {};
  uint32_t num = sizeof(expected) / sizeof(struct test_ll_simple_struct);

  TEST_MESSAGE("[LL_TEST]: erase");

  for (size_t i = 0; i < sizeof(input) / sizeof(struct test_ll_simple_struct); i++)
  {
    ll->insert(ll, &input[i], i);
  }

  TEST_ASSERT_TRUE(ll->erase(ll, 1));
  TEST_ASSERT_TRUE(ll->erase(ll, 2));
  TEST_ASSERT_TRUE(ll->erase(ll, 3));
  TEST_ASSERT_TRUE(ll->erase(ll, 4));
  TEST_ASSERT_TRUE(ll->erase(ll, 5));

  for (size_t i = 0; i < sizeof(expected) / sizeof(struct test_ll_simple_struct); i++)
  {
    ll->at(ll, &output[i], i);
  }

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, output, sizeof(struct test_ll_simple_struct),
                                 sizeof(expected) / sizeof(struct test_ll_simple_struct));
}

/**
 * @brief The unit test verifies that method `size` return valid size after `push front` method.
 */
void test_TestCase_11(void)
{
  struct test_ll_simple_struct input[] = {
      {.a = 93, .b = 93, .c = 93}, {.a = 11, .b = 11, .c = 11},    {.a = 67, .b = 67, .c = 67},
      {.a = 33, .b = 33, .c = 33}, {.a = 66, .b = 66, .c = 66},    {.a = 55, .b = 55, .c = 55},
      {.a = 54, .b = 54, .c = 54}, {.a = 77, .b = 77, .c = 77},    {.a = 77, .b = 77, .c = 77},
      {.a = 99, .b = 99, .c = 99}, {.a = 100, .b = 100, .c = 100}, {.a = 90, .b = 90, .c = 90},
      {.a = 90, .b = 90, .c = 90}, {.a = 56, .b = 56, .c = 56},    {.a = 1, .b = 1, .c = 1},
  };

  struct test_ll_simple_struct output[sizeof(input) / sizeof(struct test_ll_simple_struct)] = {};

  TEST_MESSAGE("[LL_TEST]: size #1");

  for (size_t i = 0; i < sizeof(input) / sizeof(struct test_ll_simple_struct); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT16(i, size);
    ll->push_front(ll, &input[i]);
  }

  for (size_t i = 0; i < sizeof(output) / sizeof(struct test_ll_simple_struct); i++)
  {
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT16(sizeof(output) / sizeof(struct test_ll_simple_struct) - i, size);
    ll->pop_front(ll, &output[i]);
  }
}
