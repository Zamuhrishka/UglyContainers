/**
 * @file test_bst_TestSuite2.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-05-06
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdint.h>
#include <stdbool.h>

#include "core/allocator_if.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "structs/bt/bt.h"
#include "contants.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static bt_t* bst = NULL;
static uint8_t input[] = { 8, 3, 10, 2, 6, 14, 4, 7, 13, 16, 17 };
static uint8_t output[sizeof(input)/sizeof(input[0])] = {};
static size_t offset = 0;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static cmp_t compare_u8(void* value1, void* value2)
{
    uint8_t* v1 = (uint8_t*)value1;
    uint8_t* v2 = (uint8_t*)value2;

    return (*v1 == *v2) ? EQ : (*v1 > *v2) ? GT : LE;
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    bst = bt_create(sizeof(uint8_t), compare_u8);
    TEST_ASSERT_NOT_NULL(bst);

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bt_insert(bst, &input[i]));
    }
}

void tearDown(void)
{
    bt_delete(bst);
}

void test_init(void)
{
    TEST_MESSAGE("Binary Search Tree Min/Max Tests");
}

/**
 * \brief Test case to verify binary search tree creation
 */
void test_TestCase_0(void)
{
    TEST_MESSAGE("Creation Test");
    TEST_ASSERT_NOT_NULL(bst);
}

/**
 * @brief The unit test verifies the getting min
 *        element from a binary search tree.
 */
void test_TestCase_1(void)
{
    TEST_MESSAGE("Simple Min Test");
    uint8_t* min = bt_min(bst);
    TEST_ASSERT_EQUAL_UINT8(2, *min);
}

/**
 * @brief The unit test verifies the getting max
 *        element from a binary search tree.
 */
void test_TestCase_2(void)
{
    TEST_MESSAGE("Simple Max Test");
    uint8_t* max = bt_max(bst);
    TEST_ASSERT_EQUAL_UINT8(17, *max);
}

/**
 * @brief The unit test verifies the getting min
 *        element after insert new min element.
 */
void test_TestCase_3(void)
{
    TEST_MESSAGE("Insert New Min Element Test");

    uint8_t new_min = 1;
    TEST_ASSERT_TRUE(bt_insert(bst, &new_min));

    uint8_t* output = bt_min(bst);
    TEST_ASSERT_EQUAL_UINT8(new_min, *output);
}

/**
 * @brief The unit test verifies the getting max
 *        element after insert new min element.
 */
void test_TestCase_4(void)
{
    TEST_MESSAGE("Insert New Max Element Test");

    uint8_t new_max = 100;
    TEST_ASSERT_TRUE(bt_insert(bst, &new_max));

    uint8_t* output = bt_max(bst);
    TEST_ASSERT_EQUAL_UINT8(new_max, *output);
}

/**
 * @brief The unit test verifies the getting min
 *        element after remove old min element.
 */
void test_TestCase_5(void)
{
    TEST_MESSAGE("Insert New Min Element Test");

    uint8_t old_min = 2;
    TEST_ASSERT_TRUE(bt_remove(bst, &old_min));

    uint8_t* output = bt_min(bst);
    TEST_ASSERT_EQUAL_UINT8(3, *output);
}

/**
 * @brief The unit test verifies the getting max
 *        element after remove old min element.
 */
void test_TestCase_6(void)
{
    TEST_MESSAGE("Insert New Max Element Test");

    uint8_t old_max = 17;
    TEST_ASSERT_TRUE(bt_remove(bst, &old_max));

    uint8_t* output = bt_max(bst);
    TEST_ASSERT_EQUAL_UINT8(16, *output);
}
