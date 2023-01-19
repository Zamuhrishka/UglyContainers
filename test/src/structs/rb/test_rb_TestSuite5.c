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
#define RB_MAX_SIZE 32
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static ring_buffer_t* rb = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    rb = rb_create(RB_MAX_SIZE, sizeof(uint32_t));
}

void tearDown(void)
{
    rb_delete(&rb);
}

void test_init(void)
{
    TEST_MESSAGE("RingBuffer Limits Tests");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("RingBuffer create test");
    TEST_ASSERT_NOT_NULL(rb);
}

void test_TestCase_1(void)
{
	uint16_t data = 0x55;

    TEST_MESSAGE("RingBuffer GET EMPTY test");

    TEST_ASSERT_FALSE(rb_get(rb, &data));
}

void test_TestCase_2(void)
{
	uint16_t data = 0x55;

    TEST_MESSAGE("RingBuffer PEEK EMPTY test");

    TEST_ASSERT_FALSE(rb_peek(rb, &data));
}

void test_TestCase_3(void)
{
	uint16_t data = 0x55;

    TEST_MESSAGE("RingBuffer ADD FULL test");

    for (size_t i = 0; i < RB_MAX_SIZE; i++)
    {
        rb_add(rb, &data);
    }
    
    TEST_ASSERT_FALSE(rb_add(rb, &data));    
}

void test_TestCase_4(void)
{
	uint16_t data = 0x55;

    TEST_MESSAGE("RingBuffer SIZE EMPTY test");

    size_t size = rb_size(rb);
    TEST_ASSERT_EQUAL_UINT32(0, size);
}
