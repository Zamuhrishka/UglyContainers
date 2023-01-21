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
#include "structs/rb/ring_buffer.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static ring_buffer_t* rb = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    rb = rb_create(32, sizeof(uint32_t));
}

void tearDown(void)
{
    rb_delete(&rb);
}

void test_init(void)
{
    TEST_MESSAGE("RingBuffer Simple Tests");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("[RB_TEST]: create");
    TEST_ASSERT_NOT_NULL(rb);
}

void test_TestCase_1(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("[RB_TEST]: add");
    TEST_ASSERT_TRUE(rb_add(rb, &data));
}

void test_TestCase_2(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("[RB_TEST]: is empty");
    TEST_ASSERT_TRUE(rb_is_empty(rb));
    rb_add(rb, &data);
    TEST_ASSERT_FALSE(rb_is_empty(rb));
}

void test_TestCase_3(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("[RB_TEST]: size");
    rb_add(rb, &data);
    size_t size = rb_size(rb);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}


void test_TestCase_4(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("[RB_TEST]: get");
    rb_add(rb, &data);
    TEST_ASSERT_TRUE(rb_get(rb, &data));
}

void test_TestCase_5(void)
{
	uint32_t data = 0x55;

    TEST_MESSAGE("[RB_TEST]: peek");
    rb_add(rb, &data);
    TEST_ASSERT_TRUE(rb_peek(rb, &data));
}
