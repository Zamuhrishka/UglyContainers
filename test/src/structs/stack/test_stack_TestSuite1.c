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
    TEST_MESSAGE("Stack Simple Tests For 32-bit Data");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("Stack create test");
    TEST_ASSERT_NOT_NULL(stack);
}

void test_TestCase_1(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("Stack PUSH test");

    TEST_ASSERT_TRUE(stack_push(stack, &data));
}

void test_TestCase_2(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("Stack EMPTY test");

    TEST_ASSERT_TRUE(stack_empty(stack));

    stack_push(stack, &data);

    TEST_ASSERT_FALSE(stack_empty(stack));
}

void test_TestCase_3(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("Stack SIZE test");

    stack_push(stack, &data);
    size_t size = stack_size(stack);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}


void test_TestCase_4(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("Stack POP test");

    stack_push(stack, &data);
    TEST_ASSERT_TRUE(stack_pop(stack, &data));
}

void test_TestCase_5(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("Stack PEEK test");

    stack_push(stack, &data);
    TEST_ASSERT_TRUE(stack_peek(stack, &data));
}

