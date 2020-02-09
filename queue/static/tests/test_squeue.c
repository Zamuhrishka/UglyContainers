// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**********************************************************************************************
* @file    		test_squeue.c
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @brief		Functions for testing dfifo library.
***********************************************************************************************/
//_____ I N C L U D E S _______________________________________________________________________
#include "squeue.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cmockery.h"
#ifdef DEBUG
	#include "debug.h"
#endif
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
#define UNIT_TESTING	1
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
//_____ S T A T I Ñ  F U N C T I O N   D E F I N I T I O N   __________________________________
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
#if UNIT_TESTING
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size,
                          const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);

#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif // UNIT_TESTING

static void squeue_uint8_main_test(void **state)
{
	squeue_t queue;
	uint8_t outputData[QUEUE_SIZE];
	uint8_t inputData[QUEUE_SIZE];
	size_t j = 0;

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	assert_true(squeue_init(&queue, sizeof(uint8_t)));

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(squeue_enqueue(&queue, &inputData[i]));
		assert_int_equal(squeue_size(&queue), ++j);
	}

	j = QUEUE_SIZE;
	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_int_equal(squeue_size(&queue), j--);
		assert_true(squeue_denqueue(&queue, &outputData[i]));
	}

	assert_memory_equal(inputData, outputData, QUEUE_SIZE);
}

static void squeue_uint16_main_test(void **state)
{
	squeue_t queue;
	uint16_t outputData[QUEUE_SIZE];
	uint16_t inputData[QUEUE_SIZE];
	size_t j = 0;

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	assert_true(squeue_init(&queue, sizeof(uint16_t)));

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint16_t); i++)
	{
		assert_true(squeue_enqueue(&queue, &inputData[i]));
		assert_int_equal(squeue_size(&queue), ++j);
	}

	j = QUEUE_SIZE/sizeof(uint16_t);
	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint16_t); i++)
	{
		assert_int_equal(squeue_size(&queue), j--);
		assert_true(squeue_denqueue(&queue, &outputData[i]));
	}

	assert_memory_equal(inputData, outputData, QUEUE_SIZE/sizeof(uint16_t));
}

static void squeue_uint32_main_test(void **state)
{
	squeue_t queue;
	uint32_t outputData[QUEUE_SIZE/sizeof(uint32_t)];
	uint32_t inputData[QUEUE_SIZE/sizeof(uint32_t)];
	size_t j = 0;

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint32_t); i++) {
		inputData[i] = i;
	}

	assert_true(squeue_init(&queue, sizeof(uint32_t)));

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint32_t); i++)
	{
		assert_true(squeue_enqueue(&queue, &inputData[i]));
		assert_int_equal(squeue_size(&queue), ++j);
	}

	j = QUEUE_SIZE/sizeof(uint32_t);
	for(size_t i = 0; i < QUEUE_SIZE/sizeof(uint32_t); i++)
	{
		assert_int_equal(squeue_size(&queue), j--);
		assert_true(squeue_denqueue(&queue, &outputData[i]));
	}

	assert_memory_equal(inputData, outputData, QUEUE_SIZE/sizeof(uint32_t));
}

static void squeue_struct_main_test(void **state)
{
	typedef struct
	{
		uint8_t a;
		uint16_t b;
		uint32_t c;
	}	template_t;

	squeue_t queue;
	template_t outputData[QUEUE_SIZE/sizeof(template_t)];
	template_t inputData[QUEUE_SIZE/sizeof(template_t)];
	size_t j = 0;

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		inputData[i].a = i;
		inputData[i].b = i * 100;
		inputData[i].c = i * 100;
	}

	assert_true(squeue_init(&queue, sizeof(template_t)));

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		assert_true(squeue_enqueue(&queue, (void*)&inputData[i]));
		assert_int_equal(squeue_size(&queue), ++j);
	}

	j = QUEUE_SIZE/sizeof(template_t);
	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		assert_int_equal(squeue_size(&queue), j--);
		assert_true(squeue_denqueue(&queue, (void*)&outputData[i]));
	}

	for(size_t i = 0; i < QUEUE_SIZE/sizeof(template_t); i++)
	{
		assert_memory_equal(&inputData[i], &outputData[i], sizeof(template_t));
	}

}

static void squeue_empty_denqueue_test(void **state)
{
	squeue_t queue;
	uint8_t tmpData = 0;

	assert_true(squeue_init(&queue, sizeof(uint8_t)));
	assert_false(squeue_denqueue(&queue, &tmpData));
}

static void squeue_full_enqueue_test(void **state)
{
	squeue_t queue;
	uint8_t data[QUEUE_SIZE];

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		data[i] = i;
	}
	assert_true(squeue_init(&queue, sizeof(uint8_t)));

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		assert_true(squeue_enqueue(&queue, &data[i]));
	}

	assert_false(squeue_enqueue(&queue, &data[0]));
}

void squeue_test(void)
{
  const UnitTest tests[] = {
		  unit_test(squeue_struct_main_test),
		  unit_test(squeue_uint8_main_test),
		  unit_test(squeue_uint16_main_test),
		  unit_test(squeue_uint32_main_test),
		  unit_test(squeue_empty_denqueue_test),
		  unit_test(squeue_full_enqueue_test),
  };

  run_tests(tests);
}
