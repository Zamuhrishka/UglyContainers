/**
 * @file test_ll.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdint.h>
#include <stdbool.h>

#include "core/allocator_if.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "structs/stack/stack.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static stack_t* stack = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    stack = stack_create(sizeof(uint32_t));
}

void tearDown(void)
{
    stack_delete(&stack);
}

void test_init(void)
{
    TEST_MESSAGE("Stack Complex Tests");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("[STACK_TEST]: create");
    TEST_ASSERT_NOT_NULL(stack);
}

void test_TestCase_1(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {1, 562610, 907163, 90197, 10021, 99999, 771535, 77777, 54519, 55555, 66, 33333, 67793, 11111,93274};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[STACK_TEST]: push/pop");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(stack_push(stack, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(stack_pop(stack, &output[i]));
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_2(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {1, 562610, 907163, 90197, 10021, 99999, 771535, 77777, 54519, 55555, 66, 33333, 67793, 11111,93274};
    uint32_t output = 0;

    TEST_MESSAGE("[STACK_TEST]: push/peek");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(stack_push(stack, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(stack_peek(stack, &output));
        TEST_ASSERT_EQUAL_UINT32(expected[i], output);
        stack_pop(stack, &output);
    }
}

void test_TestCase_3(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[STACK_TEST]: size #1");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = stack_size(stack);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        stack_push(stack, &input[i]);
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        size_t size = stack_size(stack);
        TEST_ASSERT_EQUAL_UINT32(sizeof(input)/sizeof(uint32_t), size);
        stack_peek(stack, &output[i]);
    }
}

void test_TestCase_4(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[STACK_TEST]: size #2");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = stack_size(stack);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        stack_push(stack, &input[i]);
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        size_t size = stack_size(stack);
        TEST_ASSERT_EQUAL_UINT32(sizeof(input)/sizeof(uint32_t) - i, size);
        stack_pop(stack, &output[i]);
    }
}