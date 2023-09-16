/**
 * @file test_ll.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

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
  TEST_MESSAGE("Queue Simple Tests");
}

void test_TestCase_0(void)
{
  TEST_MESSAGE("[QUEUE_TEST]: create");
  TEST_ASSERT_NOT_NULL(queue);
}

void test_TestCase_1(void)
{
  uint32_t data = 0x55;
  TEST_MESSAGE("[QUEUE_TEST]: enqueue");
  TEST_ASSERT_TRUE(queue_add(queue, &data));
}

void test_TestCase_2(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: is empty");
  TEST_ASSERT_TRUE(queue_empty(queue));
  queue_add(queue, &data);
  TEST_ASSERT_FALSE(queue_empty(queue));
}

void test_TestCase_3(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: size");
  queue_add(queue, &data);
  size_t size = queue_size(queue);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

void test_TestCase_4(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: dequeue");
  queue_add(queue, &data);
  TEST_ASSERT_TRUE(queue_get(queue, &data));
}

void test_TestCase_5(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: peek");
  queue_add(queue, &data);
  TEST_ASSERT_TRUE(queue_peek(queue, &data));
}
