/**
 * @file    test_linkedlist_TestSuite5.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of unit tests for Linked List which checks the corner cases.
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
  ll = linked_list_create(sizeof(uint32_t));
}

void tearDown(void)
{
  linked_list_delete(&ll);
}

void test_init(void)
{
  TEST_MESSAGE("Linked List Corner Cases Tests");
}

/**
 * \brief Test case to verify linked list creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[LL_TEST]: creation");
  TEST_ASSERT_NOT_NULL(ll);
}

/**
 * @brief The unit test verifies valid behaviour during pop front from empty
 *        linked list.
 */
void test_TestCase_1(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[LL_TEST]: pop front from empty");
  TEST_ASSERT_FALSE(ll->pop_front(ll, &input));
}

/**
 * @brief The unit test verifies valid behaviour during pop back from empty
 *        linked list.
 */
void test_TestCase_2(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[LL_TEST]: pop back from empty");
  TEST_ASSERT_FALSE(ll->pop_back(ll, &input));
}

/**
 * @brief The unit test verifies valid behaviour during insert data in
 *        overflow index.
 */
void test_TestCase_3(void)
{
  uint32_t input = 0x55555555;
  TEST_MESSAGE("[LL_TEST]: pop insert in to overflow index");
  TEST_ASSERT_FALSE(ll->insert(ll, &input, 2));
}

/**
 * @brief The unit test verifies valid behaviour during at operation from
 *        empty linked list.
 */
void test_TestCase_4(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[LL_TEST]: at from empty");
  TEST_ASSERT_FALSE(ll->at(ll, &input, 0));
}

/**
 * @brief The unit test verifies valid behaviour during erase operation from
 *        empty linked list.
 */
void test_TestCase_5(void)
{
  TEST_MESSAGE("[LL_TEST]: erase from empty");
  TEST_ASSERT_FALSE(ll->erase(ll, 0));
}

/**
 * @brief The unit test verifies valid behaviour during erase data from
 *        overflow index.
 */
void test_TestCase_6(void)
{
  uint32_t input = 0x55555555;

  TEST_MESSAGE("[LL_TEST]: erase overflow index");

  ll->insert(ll, &input, 0);

  TEST_ASSERT_FALSE(ll->erase(ll, 2));
}

/**
 * @brief The unit test verifies valid behaviour during size operation for
 *        empty linked list.
 */
void test_TestCase_7(void)
{
  TEST_MESSAGE("[LL_TEST]: size of empty");
  size_t size = ll->size(ll);
  TEST_ASSERT_EQUAL_UINT32(0, size);
}

/**
 * @brief The unit test verifies valid behaviour during extract operation for
 *        empty linked list.
 */
void test_TestCase_8(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[LL_TEST]: extract from empty");
  TEST_ASSERT_FALSE(ll->extract(ll, &input, 0));
}

/**
 * @brief The unit test verifies valid behaviour during extract data from
 *        overflow index.
 */
void test_TestCase_9(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[LL_TEST]: extract overflow index");
  TEST_ASSERT_FALSE(ll->extract(ll, &input, 2));
}

/**
 * @brief The unit test verifies valid behaviour during replace operation for
 *        empty linked list.
 */
void test_TestCase_10(void)
{
  uint32_t input = 0;
  TEST_MESSAGE("[LL_TEST]: replace from empty");
  TEST_ASSERT_FALSE(ll->replace(ll, &input, 0));
}

/**
 * @brief The unit test verifies valid behaviour during clear operation for
 *        empty linked list.
 */
void test_TestCase_11(void)
{
  TEST_MESSAGE("[LL_TEST]: clear empty");
  TEST_ASSERT_TRUE(ll->clear(ll));
}
