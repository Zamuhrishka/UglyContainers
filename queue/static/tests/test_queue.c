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
#include <assert.h>
#include "cmockery.h"
#ifdef DEBUG
	#include "debug.h"
#endif


// If unit testing is enabled override assert with mock_assert().
#if UNIT_TESTING
extern void mock_assert(const int result, const char* const expression, 
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);


extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size, 
                          const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);

#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif // UNIT_TESTING

//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
#define QUEUE_SIZE	32

static queue_t* queue = NULL;

typedef struct
{
	uint8_t a;
	uint16_t b;
	uint32_t c;
}	template_t;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
//_____ S T A T I �  F U N C T I O N   D E F I N I T I O N   __________________________________
static void preparation_data(void **state)
{

}
static void destroy_data(void **state)
{
	queue_delete(&queue);
}






static void queue_creation_test(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);
}


static void queue_creation_failure_test(void **state)
{
	expect_assert_failure(queue_create(QUEUE_SIZE, sizeof(uint8_t)));

	expect_assert_failure(queue_reg_mem_alloc_cb(NULL));
	expect_assert_failure(queue_reg_mem_free_cb(NULL));	
}







static void queue_uint8_main_test(void **state)
{
	size_t size = 0;
	uint8_t outputData[QUEUE_SIZE] = {0};
	uint8_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	size = queue_free_space(queue);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_enqueue(queue, &inputData[i]));
	}

	assert_int_equal(queue_size(queue), size);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_denqueue(queue, &outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);
	assert_memory_equal(inputData, outputData, size);
}

static void queue_uint16_main_test(void **state)
{
	size_t size = 0;
	uint16_t outputData[QUEUE_SIZE] = {0};
	uint16_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint16_t));
	assert_int_not_equal(queue, NULL);

	size = queue_free_space(queue);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_enqueue(queue, &inputData[i]));
	}

	assert_int_equal(queue_size(queue), size);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_denqueue(queue, &outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);
	assert_memory_equal(inputData, outputData, size);
}

static void queue_uint32_main_test(void **state)
{
	size_t size = 0;
	uint32_t outputData[QUEUE_SIZE] = {0};
	uint32_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint32_t));
	assert_int_not_equal(queue, NULL);

	size = queue_free_space(queue);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_enqueue(queue, &inputData[i]));
	}

	assert_int_equal(queue_size(queue), size);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_denqueue(queue, &outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);
	assert_memory_equal(inputData, outputData, size);
}

static void queue_struct_main_test(void **state)
{
	size_t size = 0;
	template_t outputData[QUEUE_SIZE] = {0};
	template_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		inputData[i].a = i;
		inputData[i].b = i * 100;
		inputData[i].c = i * 100;
	}

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(template_t));
	assert_int_not_equal(queue, NULL);

	size = queue_free_space(queue);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_enqueue(queue, &inputData[i]));
	}

	assert_int_equal(queue_size(queue), size);

	for(size_t i = 0; i < size; i++)
	{
		assert_true(queue_denqueue(queue, &outputData[i]));
	}

	assert_int_equal(queue_size(queue), 0);

	for(size_t i = 0; i < size; i++)
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
	size_t size = 0;
	uint8_t data[QUEUE_SIZE];
	uint8_t inputData[QUEUE_SIZE/sizeof(uint8_t)];

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(sizeof(inputData), sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	size = queue_free_space(queue);

	for(size_t i = 0; i < size; i++) {
		data[i] = i;
	}

	for(size_t i = 0; i < size; i++) {
		assert_true(queue_enqueue(queue, &data[i]));
	}

	assert_false(queue_enqueue(queue, &data[0]));
}

static void queue_peek_test(void **state)
{
	size_t size = 0;
	uint8_t tmpData = 0;
	uint8_t data[QUEUE_SIZE];

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	size = queue_free_space(queue);

	for(size_t i = 0; i < size; i++) {
		data[i] = i;
	}

	for(size_t i = 0; i < size; i++) {
		assert_true(queue_enqueue(queue, &data[i]));
	}

	assert_true(queue_peek(queue, &tmpData));
	assert_int_equal(queue_size(queue), QUEUE_SIZE);

	assert_true(queue_peek(queue, &tmpData));
	assert_int_equal(queue_size(queue), QUEUE_SIZE);
}

static void queue_flush_test(void **state)
{
	size_t size = 0;
	uint8_t tmpData = 0;
	uint8_t data[QUEUE_SIZE];

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	size = queue_free_space(queue);

	for(size_t i = 0; i < size; i++) {
		data[i] = i;
	}

	for(size_t i = 0; i < size; i++) {
		assert_true(queue_enqueue(queue, &data[i]));
	}

	assert_int_equal(queue_size(queue), size);

	queue_flush(queue);
	assert_int_equal(queue_size(queue), 0);

	assert_false(queue_denqueue(queue, &tmpData));
}
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
void queue_test(void)
{
  const UnitTest tests[] =
  {
		  unit_test_setup_teardown(queue_uint8_main_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(queue_uint16_main_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(queue_uint32_main_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(queue_struct_main_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(queue_empty_denqueue_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(queue_full_enqueue_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(queue_peek_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(queue_flush_test, preparation_data, destroy_data),


		  unit_test(queue_creation_test),
		  unit_test(queue_creation_failure_test),
  };

  run_tests(tests);
}
