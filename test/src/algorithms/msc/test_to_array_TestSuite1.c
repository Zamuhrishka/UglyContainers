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

#include "algorithms/msc/msc.h"
#include "allocator_if.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "structs/queue/queue.h"
#include "structs/rb/ring_buffer.h"
#include "structs/stack/stack.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
#define RB_MAX_SIZE 30
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static queue_t* queue = NULL;
static stack_t* stack = NULL;
static ring_buffer_t* rb = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  queue = queue_create(sizeof(uint32_t));
  stack = stack_create(sizeof(uint32_t));
  rb = rb_create(RB_MAX_SIZE, sizeof(uint32_t));
}

void tearDown(void)
{
  queue_delete(&queue);
  stack_delete(&stack);
  rb_delete(&rb);
}

void test_init(void)
{
  TEST_MESSAGE("To/from array algorithms simple tests");
}

void test_TestCase_0(void)
{
  TEST_MESSAGE("[ALG__TO/FROM_ARRAY]: create");
  TEST_ASSERT_NOT_NULL(queue);
}

void test_TestCase_1(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[ALG__TO_ARRAY]: Queue");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(queue_add(queue, &input[i]));
  }

  TEST_ASSERT_TRUE(to_array((container_t*)queue, output, sizeof(expected) / sizeof(uint32_t), sizeof(uint32_t)));

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected) / sizeof(uint32_t));
}

void test_TestCase_2(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[ALG__FROM_ARRAY]: Queue");

  TEST_ASSERT_TRUE(from_array((container_t*)queue, input, sizeof(input) / sizeof(uint32_t), sizeof(uint32_t)));

  for (size_t i = 0; i < sizeof(output) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(queue_get(queue, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected) / sizeof(uint32_t));
}

void test_TestCase_3(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[ALG__TO_ARRAY]: Stack");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(stack_push(stack, &input[i]));
  }

  TEST_ASSERT_TRUE(to_array((container_t*)stack, output, sizeof(expected) / sizeof(uint32_t), sizeof(uint32_t)));

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected) / sizeof(uint32_t));
}

void test_TestCase_4(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {1,     562610, 907163, 90197, 10021, 99999, 771535, 77777,
                         54519, 55555,  66,     33333, 67793, 11111, 93274};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[ALG__FROM_ARRAY]: Stack");

  TEST_ASSERT_TRUE(from_array((container_t*)stack, input, sizeof(input) / sizeof(uint32_t), sizeof(uint32_t)));

  size_t size = stack_size((container_t*)stack);
  TEST_ASSERT_EQUAL_UINT32(size, sizeof(input) / sizeof(uint32_t));

  for (size_t i = 0; i < sizeof(output) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(stack_pop(stack, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected) / sizeof(uint32_t));
}

void test_TestCase_5(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[ALG__TO_ARRAY]: RingBuffer");
  TEST_IGNORE_MESSAGE("This test not implemented!");

  // for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
  // {
  //     TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  // }

  // TEST_ASSERT_TRUE(to_array((container_t*)rb, output, sizeof(expected)/sizeof(uint32_t), sizeof(uint32_t)));

  // TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_6(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[ALG__FROM_ARRAY]: RingBuffer");
  TEST_IGNORE_MESSAGE("This test not implemented!");

  // TEST_ASSERT_TRUE(from_array((container_t*)rb, input, sizeof(input)/sizeof(uint32_t), sizeof(uint32_t)));

  // for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
  // {
  //     TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
  // }

  // TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}
