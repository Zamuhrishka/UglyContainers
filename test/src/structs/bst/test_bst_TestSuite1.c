/**
 * @file test_bst_TestSuite2.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief  Test cases for the binary search tree insert and remove functions
 *         implemented in bt.h.
 * @date 2023-05-06
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "contants.h"
#include "core/allocator_if.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "structs/bst/bst.h"

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
    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Creation Test");
    TEST_ASSERT_NOT_NULL(bst);

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the insertion of
 *        multiple elements into a binary search tree.
 */
void test_TestCase_1(void)
{
    uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Simple Insert Test");

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the insertion of
 *        duplicate elements into a binary search tree.
 */
void test_TestCase_2(void)
{
    uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Simple Insert Duplicate Test");

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of
 *        element from empty binary search tree.
 */
void test_TestCase_3(void)
{
    uint8_t output = 0;

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Remove Operation Edge Condition Test");
    TEST_ASSERT_FALSE(bst_remove(bst, &output));

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of
 *        one element from a binary search tree.
 */
void test_TestCase_4(void)
{
    uint8_t element = 8;

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Simple Remove Test");

    TEST_ASSERT_TRUE(bst_insert(bst, &element));
    TEST_ASSERT_TRUE(bst_remove(bst, &element));

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of min
 *        element from binary search tree.
 */
void test_TestCase_5(void)
{
    uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Remove Min Element Test");

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    uint8_t min = 1;

    TEST_ASSERT_TRUE(bst_remove(bst, &min));

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of max
 *        element from binary search tree.
 */
void test_TestCase_6(void)
{
    uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Remove Max Element Test");

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    // uint8_t max = 14;
    // TEST_ASSERT_TRUE(bst_remove(bst, &max));
    TEST_ASSERT_TRUE(bst_remove(bst, &(uint8_t){14}));

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of left
 *        element from binary search tree.
 */
void test_TestCase_7(void)
{
    uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Remove Left Element Test");

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    uint8_t left_node = 3;

    TEST_ASSERT_TRUE(bst_remove(bst, &left_node));

    // FIXME: Need to figure out why this delete function is break the build process
    // bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of right
 *        element from binary search tree.
 */
void test_TestCase_8(void)
{
    uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Remove Right Element Test");

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    uint8_t right_node = 10;

    TEST_ASSERT_TRUE(bst_remove(bst, &right_node));

    bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of root
 *        elements from binary search tree.
 */
void test_TestCase_9(void)
{
    uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

    TEST_MESSAGE("Remove Root Element Test");

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }

    uint8_t root = 8;

    TEST_ASSERT_TRUE(bst_remove(bst, &root));

    // bst_delete(&bst);
}

/**
 * @brief The unit test verifies the remove of: min, max,
 *        left, right and root elements from binary search tree.
 */
// void test_TestCase_10(void)
// {
//     uint8_t input[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

//     bst_t* bst = bst_create(sizeof(uint8_t), compare_u8);

//     TEST_MESSAGE("Simple Multiple Remove Test");

//     for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++)
//     {
//         TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
//     }

//     uint8_t root = 8;
//     uint8_t min = 1;
//     uint8_t max = 14;
//     uint8_t left_node = 3;
//     uint8_t right_node = 10;

//     TEST_ASSERT_TRUE(bst_remove(bst, &min));
//     TEST_ASSERT_TRUE(bst_remove(bst, &max));
//     TEST_ASSERT_TRUE(bst_remove(bst, &left_node));
//     TEST_ASSERT_TRUE(bst_remove(bst, &right_node));
//     TEST_ASSERT_TRUE(bst_remove(bst, &root));

//     // bst_delete(&bst);
// }
