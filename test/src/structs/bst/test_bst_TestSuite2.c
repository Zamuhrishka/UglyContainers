/**
 * @file    test_bst_TestSuite1.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Test cases for the binary search tree traversal functions
 *          implemented in bt.h.
 * @date    2023-02-05
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
static uint8_t input[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };
static uint8_t output[sizeof(input)/sizeof(input[0])] = {};
static size_t offset = 0;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static cmp_t compare_u8(void* value1, void* value2)
{
    uint8_t* v1 = (uint8_t*)value1;
    uint8_t* v2 = (uint8_t*)value2;

    return (*v1 == *v2) ? EQ : (*v1 > *v2) ? GT : LE;
}

void callback(void* data)
{
    output[offset++] = (uint8_t)*((uint8_t*)data);
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    bst = bt_create(sizeof(uint8_t), compare_u8);
    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        bt_insert(bst, &input[i]);
    }
}

void tearDown(void)
{
    bt_delete(bst);
}

void test_init(void)
{
    TEST_MESSAGE("Binary Search Tree Traversal Functions Tests");
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
 * @brief Test case to verify the pre-order traversal of a binary search tree
 */
void test_TestCase_1(void)
{
    uint8_t expected[] = { 8, 3, 1, 6, 4, 7, 10, 14, 13 };

    TEST_MESSAGE("Pre-Order Traversal Test");

    bt_pre_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }

    offset = 0;
}

/**
 * \brief Test case to verify the post-order traversal function of a binary search tree.
 */
void test_TestCase_2(void)
{
    uint8_t expected[] = { 1, 4, 7, 6, 3, 13, 14, 10, 8 };

    TEST_MESSAGE("Post-Order Traversal Test");

    bt_post_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }

    offset = 0;
}

/**
 * \brief Test case to verify the in-order traversal function of a binary search tree.
 */
void test_TestCase_3(void)
{
    uint8_t expected[] = { 1, 3, 4, 6, 7, 8, 10, 13, 14 };

    TEST_MESSAGE("In-Order Traversal Test");

    bt_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }

    offset = 0;
}