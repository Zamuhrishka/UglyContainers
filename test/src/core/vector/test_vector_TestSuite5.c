/**
 * @file    test_linkedlist_TestSuite5.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of unit tests for Vector which checks the corner cases.
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "allocator_if.h"
#include "vector.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
#define DEFAULT_CAPACITY 10
#define DEFAULT_BIGGER_CAPACITY 15
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static vector_t* vector = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  vector = vector_create(sizeof(uint32_t));
}

void tearDown(void)
{
  vector_delete(&vector);
}

void test_init(void)
{
  TEST_MESSAGE("Vector Limits Tests");
}

/**
 * \brief Test case to verify vector creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[VECTOR_TEST]: creation");
  TEST_ASSERT_NOT_NULL(vector);
}

/**
 * @brief The unit test verifies valid behaviour during pop front from empty
 *        vector.
 */
void test_TestCase_1(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[VECTOR_TEST]: pop front from empty");
  TEST_ASSERT_FALSE(vector->pop_front(vector, &input));
}

/**
 * @brief The unit test verifies valid behaviour during pop back from empty
 *        vector.
 */
void test_TestCase_2(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[VECTOR_TEST]: pop back from empty");
  TEST_ASSERT_FALSE(vector->pop_back(vector, &input));
}

/**
 * @brief The unit test verifies valid behaviour during insert data in
 *        overflow index.
 */
void test_TestCase_3(void)
{
  uint32_t input = 0x55555555;
  TEST_MESSAGE("[VECTOR_TEST]: pop insert in to overflow index");
  TEST_ASSERT_FALSE(vector->insert(vector, &input, 2));
}

/**
 * @brief The unit test verifies valid behaviour during at operation from
 *        empty vector.
 */
void test_TestCase_4(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[VECTOR_TEST]: pop at from empty");
  TEST_ASSERT_FALSE(vector->at(vector, &input, 0));
}

/**
 * @brief The unit test verifies valid behaviour during erase operation from
 *        empty vector.
 */
void test_TestCase_5(void)
{
  TEST_MESSAGE("[VECTOR_TEST]: erase from empty");
  TEST_ASSERT_FALSE(vector->erase(vector, 0));
}

/**
 * @brief The unit test verifies valid behaviour during erase data from
 *        overflow index.
 */
void test_TestCase_6(void)
{
  uint32_t input = 0x55555555;

  TEST_MESSAGE("[VECTOR_TEST]: erase overflow index");

  vector->insert(vector, &input, 0);

  TEST_ASSERT_FALSE(vector->erase(vector, 2));
}

/**
 * @brief The unit test verifies valid behaviour during size operation for
 *        empty vector.
 */
void test_TestCase_7(void)
{
  TEST_MESSAGE("[VECTOR_TEST]: size of empty");
  size_t size = vector->size(vector);
  TEST_ASSERT_EQUAL_UINT32(0, size);
}

/**
 * @brief The unit test verifies valid behaviour during extract operation for
 *        empty vector.
 */
void test_TestCase_8(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[VECTOR_TEST]: extract from empty");
  TEST_ASSERT_FALSE(vector->extract(vector, &input, 0));
}

/**
 * @brief The unit test verifies valid behaviour during extract data from
 *        overflow index.
 */
void test_TestCase_9(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[VECTOR_TEST]: extract overflow index");
  TEST_ASSERT_FALSE(vector->extract(vector, &input, 2));
}

/**
 * @brief The unit test verifies valid behaviour during replace operation for
 *        empty vector.
 */
void test_TestCase_10(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[VECTOR_TEST]: replace from empty");
  TEST_ASSERT_FALSE(vector->replace(vector, &input, 0));
}

/**
 * @brief The unit test verifies valid behaviour during clear operation for
 *        empty vector.
 */
void test_TestCase_11(void)
{
  TEST_MESSAGE("[VECTOR_TEST]: clear empty");
  TEST_ASSERT_TRUE(vector->clear(vector));
}
