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
#include "structs/queue/queue.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static queue_t* queue = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    queue = queue_create(sizeof(uint32_t));
}

void tearDown(void)
{
    queue_delete(&queue);
}

void test_init(void)
{
    TEST_MESSAGE("Queue Complex Tests For 32-bit Data");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("Queue create test");
    TEST_ASSERT_NOT_NULL(queue);
}

void test_TestCase_1(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("Queue enqueue/dequeue test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(queue_enqueue(queue, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(queue_dequeue(queue, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_2(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output = 0;

    TEST_MESSAGE("Queue enqueue/peek test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(queue_enqueue(queue, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(queue_peek(queue, &output));
        TEST_ASSERT_EQUAL_UINT32(expected[i], output);
        queue_dequeue(queue, &output);
    }
}

void test_TestCase_3(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("Queue enqueue/peek size test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = queue_size(queue);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        queue_enqueue(queue, &input[i]);
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        size_t size = queue_size(queue);
        TEST_ASSERT_EQUAL_UINT32(sizeof(input)/sizeof(uint32_t), size);
        queue_peek(queue, &output[i]);        
    }
}

void test_TestCase_4(void)
{
	uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("Queue enqueue/dequeue size test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = queue_size(queue);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        queue_enqueue(queue, &input[i]);
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        size_t size = queue_size(queue);
        TEST_ASSERT_EQUAL_UINT32(sizeof(input)/sizeof(uint32_t) - i, size);
        queue_dequeue(queue, &output[i]);        
    }
}