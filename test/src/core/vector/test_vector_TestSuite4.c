/**
 * @file    test_vector_TestSuite1.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Vector 8-bit data. This list of tests just
 *          checks that all linked list methods are executes but not checks the
 *          valid execution.
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "interface/allocator_if.h"
#include "vector.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
#define DEFAULT_CAPACITY 10
#define DEFAULT_BIGGER_CAPACITY 15

struct test_vec_simple_struct
{
  uint32_t a;
  uint16_t b;
  uint8_t c;
};
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static vector_t* vector = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  vector = vector_create(sizeof(struct test_vec_simple_struct));
}

void tearDown(void)
{
  vector_delete(&vector);
}

void test_init(void)
{
  TEST_MESSAGE("Vector Simple Tests For 32-bit Data");
}

/**
 * \brief Test case to verify creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[VECTOR_TEST]: create");
  TEST_ASSERT_NOT_NULL(vector);
}

/**
 * @brief The unit test verifies the push front without resize method.
 */
void test_TestCase_1(void)
{
  struct test_vec_simple_struct input[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push front without resize");

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
  }
}

/**
 * @brief The unit test verifies the push front with resize method.
 */
void test_TestCase_2(void)
{
  struct test_vec_simple_struct input[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push front with resize");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
  }
}

/**
 * @brief The unit test verifies the pop front method.
 */
void test_TestCase_3(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[VECTOR_TEST]: pop front");

  vector->push_front(vector, &input);

  TEST_ASSERT_TRUE(vector->pop_front(vector, &input));
}

/**
 * @brief The unit test verifies the push back without resize method.
 */
void test_TestCase_4(void)
{
  struct test_vec_simple_struct input[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push back without resize");

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }
}

/**
 * @brief The unit test verifies the push back with resize method.
 */
void test_TestCase_5(void)
{
  struct test_vec_simple_struct input[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push back with resize");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }
}

/**
 * @brief The unit test verifies the pop back without resize method.
 */
void test_TestCase_6(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[VECTOR_TEST]: pop back");

  vector->push_front(vector, &input);

  TEST_ASSERT_TRUE(vector->pop_back(vector, &input));
}

/**
 * @brief The unit test verifies the insert without resize method.
 */
void test_TestCase_7(void)
{
  struct test_vec_simple_struct input[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: insert without resize");

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
  }
}

/**
 * @brief The unit test verifies the insert with resize method.
 */
void test_TestCase_8(void)
{
  struct test_vec_simple_struct input[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: insert with resize");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
  }
}

/**
 * @brief The unit test verifies the at method.
 */
void test_TestCase_9(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  struct test_vec_simple_struct output = {};

  TEST_MESSAGE("[VECTOR_TEST]: at");

  vector->insert(vector, &input, 0);

  TEST_ASSERT_TRUE(vector->at(vector, &output, 0));
}

/**
 * @brief The unit test verifies the erase without resize method.
 */
void test_TestCase_10(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[VECTOR_TEST]: erase without resize");

  vector->insert(vector, &input, 0);

  TEST_ASSERT_TRUE(vector->erase(vector, 0));
}

/**
 * @brief The unit test verifies the erase with resize method.
 */
void test_TestCase_11(void)
{
  TEST_MESSAGE("[VECTOR_TEST]: erase with resize");
  TEST_IGNORE_MESSAGE("Resize for erase haven`t implemented yet");
}

/**
 * @brief The unit test verifies the size method.
 */
void test_TestCase_12(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[VECTOR_TEST]: size");

  vector->push_front(vector, &input);

  size_t size = vector->size(vector);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

/**
 * @brief The unit test verifies the extract method.
 */
void test_TestCase_13(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  struct test_vec_simple_struct output = {};

  TEST_MESSAGE("[VECTOR_TEST]: extract");

  vector->insert(vector, &input, 0);

  TEST_ASSERT_TRUE(vector->extract(vector, &output, 0));
  TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

/**
 * @brief The unit test verifies the replace method.
 */
void test_TestCase_14(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  struct test_vec_simple_struct output = {};

  TEST_MESSAGE("[VECTOR_TEST]: replace");

  vector->insert(vector, &input, 0);

  input.a++;
  input.b++;
  input.c++;
  TEST_ASSERT_TRUE(vector->replace(vector, &input, 0));
  TEST_ASSERT_TRUE(vector->at(vector, &output, 0));
  TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

/**
 * @brief The unit test verifies the clear method.
 */
void test_TestCase_15(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

  TEST_MESSAGE("[VECTOR_TEST]: clear");

  vector->insert(vector, &input, 0);

  size_t size = vector->size(vector);
  TEST_ASSERT_EQUAL_UINT32(1, size);
  TEST_ASSERT_TRUE(vector->clear(vector));
  size = vector->size(vector);
  TEST_ASSERT_EQUAL_UINT32(0, size);
}

/**
 * @brief The unit test verifies the peek method.
 */
void test_TestCase_16(void)
{
  struct test_vec_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
  struct test_vec_simple_struct* output = NULL;

  TEST_MESSAGE("[VECTOR_TEST]: peek");

  vector->insert(vector, &input, 0);

  output = (struct test_vec_simple_struct*)vector->peek(vector, 0);
  TEST_ASSERT_TRUE(output);
  TEST_ASSERT_EQUAL_UINT32(output->a, input.a);
  TEST_ASSERT_EQUAL_UINT16(output->b, input.b);
  TEST_ASSERT_EQUAL_UINT8(output->c, input.c);
}

/**
 * @brief The unit test verifies the resize method.
 */
void test_TestCase_18(void)
{
  struct test_vec_simple_struct input = {.a = 0x55, .b = 0x55, .c = 0x55};

  TEST_MESSAGE("[VECTOR_TEST]: resize");

  vector->insert(vector, &input, 0);

  size_t size = vector->size(vector);
  TEST_ASSERT_EQUAL_UINT8(1, size);

  TEST_ASSERT_TRUE(vector->resize(vector, DEFAULT_BIGGER_CAPACITY));
  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->insert(vector, &input, 0));
  }
}
