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
#define RB_MAX_SIZE 30
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
    TEST_MESSAGE("RingBuffer Complex Tests");
    // TEST_IGNORE_MESSAGE("This TestSuite haven`t implemented");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("[RB_TEST]: create");
    TEST_ASSERT_NOT_NULL(rb);
}

void test_TestCase_1(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: is empty");

    TEST_ASSERT_TRUE(rb_is_empty(rb));

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
        TEST_ASSERT_FALSE(rb_is_empty(rb));
    }

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_FALSE(rb_is_empty(rb));
        TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
    }

    TEST_ASSERT_TRUE(rb_is_empty(rb));
}

void test_TestCase_2(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: is full");

    TEST_ASSERT_FALSE(rb_is_full(rb));

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_FALSE(rb_is_full(rb));
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    }

    TEST_ASSERT_TRUE(rb_is_full(rb));

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
        TEST_ASSERT_FALSE(rb_is_full(rb));
    }
}

void test_TestCase_3(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t expected[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: add/get #1");

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    }

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, RB_MAX_SIZE - 1);
}

void test_TestCase_4(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1 \
                                };
    uint32_t expected[RB_MAX_SIZE] = {771535, 10021, 90197, 907163, 562610, 1, 93274, 67793, 66, 54519, 771535, \
                                    10021, 90197, 907163, 562610, 11111, 22222, 33333, 44444, 55555, \
                                    66666, 77777, 88888, 999999, 11111, 22222, 33333, 44444, 55555, 66666 \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: add/get #2");

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    }

    for (size_t i = 0; i < (RB_MAX_SIZE/2) - 1; i++)
    {
        uint32_t out = 0;
        TEST_ASSERT_TRUE(rb_get(rb, &out));
    }

    for (size_t i = 0; i < (RB_MAX_SIZE/2) - 1; i++)
    {
        uint32_t in[RB_MAX_SIZE/2] = { 11111, 22222, 33333, 44444, 55555, 66666, 77777, 88888, 999999, 11111, 22222, 33333, 44444, 55555, 66666};
        TEST_ASSERT_TRUE(rb_add(rb, &in[i]));
    }

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, RB_MAX_SIZE - 1);
}

void test_TestCase_5(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t expected[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: peek");

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    }

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_peek(rb, &output[i]));
        TEST_ASSERT_EQUAL_UINT32(expected[i], output[i]);
        rb_get(rb, &output[i]);
    }
}

void test_TestCase_6(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1 \
                                };
    uint32_t expected[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1 \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: size #1");

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        size_t size = rb_size(rb);
        TEST_ASSERT_EQUAL_UINT32(size, i);
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    }

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_EQUAL_UINT32(rb_size(rb), RB_MAX_SIZE - 1 - i);
        rb_get(rb, &output[i]);
    }

    TEST_ASSERT_EQUAL_UINT32(rb_size(rb), 0);
}

void test_TestCase_7(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1 \
                                };
    uint32_t expected[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1 \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: size #2");

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        size_t size = rb_size(rb);
        TEST_ASSERT_EQUAL_UINT32(size, i);
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    }

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        rb_peek(rb, &output[i]);
        TEST_ASSERT_EQUAL_UINT32(rb_size(rb), RB_MAX_SIZE - 1);
    }
}

void test_TestCase_8(void)
{
    uint32_t input[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t expected[RB_MAX_SIZE] = { 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, \
                                };
    uint32_t output[RB_MAX_SIZE] = {};

    TEST_MESSAGE("[RB_TEST]: add/get #1");

    for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    }

    TEST_ASSERT_FALSE(rb_is_empty(rb));
    TEST_ASSERT_TRUE(rb_clear(rb));
    TEST_ASSERT_TRUE(rb_is_empty(rb));

}