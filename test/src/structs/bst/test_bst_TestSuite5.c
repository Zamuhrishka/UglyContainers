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
#include "structs/bst/bst.h"
#include "contants.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static bst_t* bst = NULL;
static uint8_t input[] = { 8, 3, 10, 2, 6, 14, 4, 7, 13 };
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
    bst = bst_create(sizeof(uint8_t), compare_u8);
    TEST_ASSERT_NOT_NULL(bst);

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_insert(bst, &input[i]));
    }
}

void tearDown(void)
{
    bst_delete(bst);
}

void test_init(void)
{
    TEST_MESSAGE("Binary Search Tree Search Tests");
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
 * @brief The unit test verifies the search function
 *        find all exist elements in binary search tree.
 */
void test_TestCase_1(void)
{
    TEST_MESSAGE("Search Exist Elements Test");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(bst_search(bst, &input[i]));
    }
}

/**
 * @brief The unit test verifies the search function
 *        don`t find not exist elements in binary search tree.
 */
void test_TestCase_2(void)
{
    TEST_MESSAGE("Search Not Exist Elements Test");

    uint8_t _input[] = { 18, 30, 100, 20, 61, 141, 48, 76, 130 };
    for (size_t i = 0; i < sizeof(_input)/sizeof(_input[0]); i++)
    {
        TEST_ASSERT_FALSE(bst_search(bst, &_input[i]));
    }
}
