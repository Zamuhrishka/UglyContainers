/**********************************************************************************************
* @file    		QAdfifo.c
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @version 		0.1
* @date    		06.06.2018
* @brief		Functions for testing dfifo library.
***********************************************************************************************/
//_____ I N C L U D E S _______________________________________________________________________
#include "queue.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "cmockery.h"
#ifdef DEBUG
	#include "debug.h"
#endif
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
#define QUEUE_SIZE	32

queue_t* queue = NULL;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
//_____ S T A T I Ñ  F U N C T I O N   D E F I N I T I O N   __________________________________
static void preparation_data(void **state)
{

}
static void destroy_data(void **state)
{
	queue_delete(&queue);
}

static void queue_uint8_main_test(void **state)
{
	uint8_t outputData[QUEUE_SIZE];
	uint8_t inputData[QUEUE_SIZE];

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(sizeof(inputData), sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(queue_enqueue(queue, &inputData[i]));
	}

	assert_int_equal(queue_size(queue), QUEUE_SIZE);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(queue_denqueue(queue, &outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);
	assert_memory_equal(inputData, outputData, QUEUE_SIZE);
}

static void queue_uint16_main_test(void **state)
{
	uint16_t outputData[QUEUE_SIZE];
	uint16_t inputData[QUEUE_SIZE];

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(sizeof(inputData), sizeof(uint16_t));
	assert_int_not_equal(queue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint16_t); i++)
	{
		assert_true(queue_enqueue(queue, &inputData[i]));
	}

	assert_int_equal(queue_size(queue), QUEUE_SIZE/sizeof(uint16_t));

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint16_t); i++)
	{
		assert_true(queue_denqueue(queue, &outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);

	assert_memory_equal(inputData, outputData, QUEUE_SIZE/sizeof(uint16_t));
}

static void queue_uint32_main_test(void **state)
{
	uint32_t outputData[QUEUE_SIZE/sizeof(uint32_t)];
	uint32_t inputData[QUEUE_SIZE/sizeof(uint32_t)];

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint32_t); i++) {
		inputData[i] = i;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(sizeof(inputData), sizeof(uint32_t));
	assert_int_not_equal(queue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint32_t); i++)
	{
		assert_true(queue_enqueue(queue, &inputData[i]));
	}

	assert_int_equal(queue_size(queue), QUEUE_SIZE/sizeof(uint32_t));

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint32_t); i++)
	{
		assert_true(queue_denqueue(queue, &outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);

	assert_memory_equal(inputData, outputData, QUEUE_SIZE/sizeof(uint32_t));
}

static void queue_struct_main_test(void **state)
{
	typedef struct
	{
		uint8_t a;
		uint16_t b;
		uint32_t c;
	}	template_t;

	template_t outputData[QUEUE_SIZE/sizeof(template_t)];
	template_t inputData[QUEUE_SIZE/sizeof(template_t)];

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		inputData[i].a = i;
		inputData[i].b = i * 100;
		inputData[i].c = i * 100;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(sizeof(inputData), sizeof(template_t));
	assert_int_not_equal(queue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		assert_true(queue_enqueue(queue, (void*)&inputData[i]));
	}

	assert_int_equal(queue_size(queue), QUEUE_SIZE/sizeof(template_t));

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		assert_true(queue_denqueue(queue, (void*)&outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		assert_memory_equal(&inputData[i], &outputData[i], sizeof(template_t));
	}

}

static void queue_empty_denqueue_test(void **state)
{
	uint8_t tmpData = 0;
	uint8_t inputData[QUEUE_SIZE/sizeof(uint8_t)];

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(sizeof(inputData), sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	assert_false(queue_denqueue(queue, &tmpData));
}

static void queue_full_enqueue_test(void **state)
{
	uint8_t data[QUEUE_SIZE];
	uint8_t inputData[QUEUE_SIZE/sizeof(uint8_t)];

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(sizeof(inputData), sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		data[i] = i;
	}

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		assert_true(queue_enqueue(queue, &data[i]));
	}

	assert_false(queue_enqueue(queue, &data[0]));
}
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
void queue_test(void)
{
  const UnitTest tests[] =
  {
		  unit_test_setup_teardown(preparation_data, queue_struct_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, queue_uint8_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, queue_uint16_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, queue_uint32_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, queue_empty_denqueue_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, queue_full_enqueue_test, destroy_data),
  };

  run_tests(tests);
}
