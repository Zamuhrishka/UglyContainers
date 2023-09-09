/**
 * @file    test_linkedlist_TestSuite4.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Linked List struct data. This list of tests just
 *          checks that all linked list methods are executes but not checks the
 *          valid execution.
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "allocator_if.h"
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
  TEST_MESSAGE("Linked List Simple Tests For struct Data");
}

/**
 * \brief Test case to verify linked list creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[LL_TEST]: create");
  TEST_ASSERT_NOT_NULL(ll);
}

/**
 * @brief The unit test verifies the push front linked list`s method.
 */
void test_TestCase_1(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  TEST_MESSAGE("[LL_TEST]: push front");
  TEST_ASSERT_TRUE(ll->push_front(ll, &input));
}

/**
 * @brief The unit test verifies the pop front linked list`s method.
 */
void test_TestCase_2(void)
{
  struct test_ll_simple_struct output = {};
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[LL_TEST]: pop front");

  ll->push_front(ll, &input);

  TEST_ASSERT_TRUE(ll->pop_front(ll, &output));
  TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

/**
 * @brief The unit test verifies the push back linked list`s method.
 */
void test_TestCase_3(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  TEST_MESSAGE("[LL_TEST]: push back");
  TEST_ASSERT_TRUE(ll->push_back(ll, &input));
}

/**
 * @brief The unit test verifies the pop back linked list`s method.
 */
void test_TestCase_4(void)
{
  struct test_ll_simple_struct output = {};
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[LL_TEST]: pop back");

  ll->push_back(ll, &input);

  TEST_ASSERT_TRUE(ll->pop_back(ll, &output));
  TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

/**
 * @brief The unit test verifies the insert linked list`s method.
 */
void test_TestCase_5(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  TEST_MESSAGE("[LL_TEST]: insert");
  TEST_ASSERT_TRUE(ll->insert(ll, &input, 0));
  TEST_ASSERT_TRUE(ll->insert(ll, &input, 0));
}

/**
 * @brief The unit test verifies the at linked list`s method.
 */
void test_TestCase_6(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  struct test_ll_simple_struct output = {};

  TEST_MESSAGE("[LL_TEST]: at");

  ll->insert(ll, &input, 0);

  TEST_ASSERT_TRUE(ll->at(ll, &output, 0));
  TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

/**
 * @brief The unit test verifies the erase linked list`s method.
 */
void test_TestCase_7(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[LL_TEST]: erase");

  ll->insert(ll, &input, 0);

  TEST_ASSERT_TRUE(ll->erase(ll, 0));
}

/**
 * @brief The unit test verifies the size linked list`s method.
 */
void test_TestCase_8(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[LL_TEST]: size");

  ll->push_front(ll, &input);

  size_t size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

/**
 * @brief The unit test verifies the extract linked list`s method.
 */
void test_TestCase_9(void)
{
  struct test_ll_simple_struct input = {.a = 0, .b = 0, .c = 0};

  TEST_MESSAGE("[LL_TEST]: extract");

  ll->insert(ll, &input, 0);

  TEST_ASSERT_TRUE(ll->extract(ll, &input, 0));
}

/**
 * @brief The unit test verifies the replace linked list`s method.
 */
void test_TestCase_10(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  struct test_ll_simple_struct output = {};

  TEST_MESSAGE("[LL_TEST]: replace");

  ll->insert(ll, &input, 0);

  input.a++;
  input.b++;
  input.c++;
  TEST_ASSERT_TRUE(ll->replace(ll, &input, 0));
  TEST_ASSERT_TRUE(ll->at(ll, &output, 0));
  TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

/**
 * @brief The unit test verifies the clear linked list`s method.
 */
void test_TestCase_11(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[LL_TEST]: clear");

  ll->insert(ll, &input, 0);

  size_t size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT32(1, size);
  TEST_ASSERT_TRUE(ll->clear(ll));
  size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT32(0, size);
}

/**
 * @brief The unit test verifies the peek linked list`s method.
 */
void test_TestCase_12(void)
{
  struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  struct test_ll_simple_struct* output = NULL;

  TEST_MESSAGE("[LL_TEST]: peek");

  ll->insert(ll, &input, 0);

  output = (struct test_ll_simple_struct*)ll->peek(ll, 0);
  TEST_ASSERT_TRUE(output);
  TEST_ASSERT_EQUAL_UINT32(output->a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output->b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output->c, input.c);
}

/**
 * @brief The unit test verifies the resize linked list`s method.
 */
void test_TestCase_13(void)
{
  TEST_MESSAGE("[LL_TEST]: resize");
  TEST_ASSERT_TRUE(ll->resize(ll, 10));
}
