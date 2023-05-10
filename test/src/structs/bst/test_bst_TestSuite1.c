/**
 * @file test_bst_TestSuite2.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief  Test cases for the binary search tree insert and remove functions
 *         implemented in bt.h.
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

}

void tearDown(void)
{

}

void test_init(void)
{
    TEST_MESSAGE("Binary Search Tree Insert/Remove Simple Tests");
}

/**
 * \brief Test case to verify binary search tree creation
 */
void test_TestCase_0(void)
{
    bt_t* bst = bt_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Creation Test");
    TEST_ASSERT_NOT_NULL(bst);

    bt_delete(bst);
}

/**
 * @brief The unit test verifies the insertion of
 *        multiple elements into a binary search tree.
 */
void test_TestCase_1(void)
{
    uint8_t input[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };

    bt_t* bst = bt_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Simple Insert Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bt_insert(bst, &input[i]));
    }

    bt_delete(bst);
}

/**
 * @brief The unit test verifies the insertion of
 *        duplicate elements into a binary search tree.
 */
void test_TestCase_2(void)
{
    uint8_t input[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };

    bt_t* bst = bt_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Simple Insert Duplicate Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bt_insert(bst, &input[i]));
        TEST_ASSERT_TRUE(bt_insert(bst, &input[i]));
    }

    bt_delete(bst);
}

/**
 * @brief The unit test verifies the remove of
 *        element from empty binary search tree.
 */
void test_TestCase_3(void)
{
    uint8_t output = 0;

    bt_t* bst = bt_create(sizeof(uint8_t), compare_u8);


    TEST_MESSAGE("Remove Operation Edge Condition Test");
    TEST_ASSERT_FALSE(bt_remove(bst, &output));

    bt_delete(bst);
}

/**
 * @brief The unit test verifies the remove of
 *        one element from a binary search tree.
 */
void test_TestCase_4(void)
{
    uint8_t element = 8;

    bt_t* bst = bt_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Simple Remove Test");

    TEST_ASSERT_TRUE(bt_insert(bst, &element));
    TEST_ASSERT_TRUE(bt_remove(bst, &element));

    bt_delete(bst);
}

/**
 * @brief The unit test verifies the remove of: min, max,
 *        left, right and root elements from binary search tree.
 */
void test_TestCase_5(void)
{
    uint8_t input[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };

    bt_t* bst = bt_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Simple Multiple Remove Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bt_insert(bst, &input[i]));
    }

    uint8_t root = 8;
    uint8_t min = 1;
    uint8_t max = 14;
    uint8_t left_node = 3;
    uint8_t right_node = 10;

    TEST_ASSERT_TRUE(bt_remove(bst, &min));
    TEST_ASSERT_TRUE(bt_remove(bst, &max));
    TEST_ASSERT_TRUE(bt_remove(bst, &left_node));
    TEST_ASSERT_TRUE(bt_remove(bst, &right_node));
    TEST_ASSERT_TRUE(bt_remove(bst, &root));

    bt_delete(bst);
}