/**
 * @file test_bst_TestSuite3.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-05-07
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdint.h>
#include <stdbool.h>

#include "core/allocator_if.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "structs/bst/bst.h"
#include "contants.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static bst_t* bst = NULL;
static uint8_t input[] = { 8, 3, 10, 2, 6, 14, 4, 7, 13, 16, 17 };
static uint8_t output[32] = {};
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
    bst = bst_create(sizeof(uint8_t), compare_u8);
}

void tearDown(void)
{
    bst_delete(bst);
}

void test_init(void)
{
    TEST_MESSAGE("Binary Search Tree Insert/Remove Complex Tests");
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
 * @brief The unit test verifies the insertion of
 *        multiple elements into a binary search tree with
 *        expected pattern.
 */
void test_TestCase_1(void)
{
    uint8_t expected[] = { 2, 3, 4, 6, 7, 8, 10, 13, 14, 16, 17 };

    TEST_MESSAGE("Multiple Insert with Pattern Verify Test");

    offset = 0;

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }

    offset = 0;
}

/**
 * @brief The unit test verifies the insertion of
 *        new min element into a binary search tree.
 */
void test_TestCase_2(void)
{
    uint8_t expected[] = { 1, 2, 3, 4, 6, 7, 8, 10, 13, 14, 16, 17 };
    uint8_t min = 1;

    TEST_MESSAGE("New Min Value Insert Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_insert(bst, &min));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/**
 * @brief The unit test verifies the insertion of
 *        new max element into a binary search tree.
 */
void test_TestCase_3(void)
{
    uint8_t expected[] = { 2, 3, 4, 6, 7, 8, 10, 13, 14, 16, 17, 50 };
    uint8_t max = 50;

    TEST_MESSAGE("New Max Value Insert Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_insert(bst, &max));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/**
 * @brief The unit test verifies the insertion of
 *        new left element into a binary search tree.
 */
void test_TestCase_4(void)
{
    uint8_t expected[] = { 2, 3, 4, 5, 6, 7, 8, 10, 13, 14, 16, 17 };
    uint8_t left = 5;

    TEST_MESSAGE("New Left Value Insert Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_insert(bst, &left));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/**
 * @brief The unit test verifies the insertion of
 *        new right element into a binary search tree.
 */
void test_TestCase_5(void)
{
    uint8_t expected[] = { 2, 3, 4, 6, 7, 8, 9, 10, 13, 14, 16, 17 };
    uint8_t right = 9;

    TEST_MESSAGE("New Right Value Insert Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_insert(bst, &right));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/**
 * @brief The unit test verifies the remove of
 *        min element from a binary search tree.
 */
void test_TestCase_6(void)
{
    uint8_t expected[] = { 3, 4, 6, 7, 8, 10, 13, 14, 16, 17 };
    uint8_t min = 2;

    TEST_MESSAGE("Min Value Remove Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_remove(bst, &min));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/**
 * @brief The unit test verifies the remove of
 *        max element from a binary search tree.
 */
void test_TestCase_7(void)
{
    uint8_t expected[] = { 2, 3, 4, 6, 7, 8, 10, 13, 14, 16 };
    uint8_t max = 17;

    TEST_MESSAGE("Max Value Remove Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_remove(bst, &max));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/**
 * @brief The unit test verifies the remove of
 *        left element from a binary search tree.
 */
void test_TestCase_8(void)
{
    uint8_t expected[] = { 2, 3, 4, 7, 8, 10, 13, 14, 16, 17 };
    uint8_t left = 6;

    TEST_MESSAGE("Left Value Remove Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_remove(bst, &left));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}


/**
 * @brief The unit test verifies the remove of
 *        right element from a binary search tree.
 */
void test_TestCase_9(void)
{
    uint8_t expected[] = { 2, 3, 4, 6, 7, 8, 13, 14, 16, 17 };
    uint8_t right = 10;

    TEST_MESSAGE("Right Value Remove Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_remove(bst, &right));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/**
 * @brief The unit test verifies the remove of
 *        element with one left child from a binary search tree.
 */
void test_TestCase_10(void)
{
    uint8_t expected[] = { 2, 3, 4, 6, 7, 8, 10, 13, 16, 17 };
    uint8_t element = 14;

    TEST_MESSAGE("Right Value Remove Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_remove(bst, &element));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}

/*
 * @brief The unit test verifies the remove of
 *        element with one right child from a binary search tree.
 */
void test_TestCase_11(void)
{
    uint8_t expected[] = { 2, 3, 4, 6, 7, 8, 10, 13, 14, 17 };
    uint8_t element = 16;

    TEST_MESSAGE("Right Value Remove Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    TEST_ASSERT_TRUE(bst_remove(bst, &element));

    offset = 0;
    bst_in_order_traversal(bst, callback);

    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(expected[i], output[i]);
    }
}
