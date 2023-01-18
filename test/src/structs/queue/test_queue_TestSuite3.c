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
    queue = queue_create(sizeof(uint8_t));
}

void tearDown(void)
{
    queue_delete(&queue);
}

void test_init(void)
{
    TEST_MESSAGE("Queue Simple Tests For 8-bit Data");
    TEST_IGNORE_MESSAGE("Need to be implemented!");
}

// void test_TestCase_0(void)
// {
//     TEST_MESSAGE("Queue create test");
//     TEST_ASSERT_NOT_NULL(queue);
// }

// void test_TestCase_1(void)
// {
// 	uint16_t data = 0x55;

//     TEST_MESSAGE("Queue ENQUEUE test");

//     TEST_ASSERT_TRUE(queue_enqueue(queue, &data));
// }

// void test_TestCase_2(void)
// {
// 	uint16_t data = 0x55;

//     TEST_MESSAGE("Queue EMPTY test");

//     TEST_ASSERT_TRUE(queue_empty(queue));

//     queue_enqueue(queue, &data);

//     TEST_ASSERT_FALSE(queue_empty(queue));
// }

// void test_TestCase_3(void)
// {
// 	uint16_t data = 0x55;

//     TEST_MESSAGE("Queue SIZE test");

//     queue_enqueue(queue, &data);
//     size_t size = queue_size(queue);
//     TEST_ASSERT_EQUAL_UINT32(1, size);
// }


// void test_TestCase_4(void)
// {
// 	uint16_t data = 0x55;

//     TEST_MESSAGE("Queue DEQUEUE test");

//     queue_enqueue(queue, &data);
//     TEST_ASSERT_TRUE(queue_dequeue(queue, &data));
// }

// void test_TestCase_5(void)
// {
// 	uint16_t data = 0x55;

//     TEST_MESSAGE("Queue PEEK test");

//     queue_enqueue(queue, &data);
//     TEST_ASSERT_TRUE(queue_peek(queue, &data));
// }

