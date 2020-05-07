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

#ifdef UNIT_TESTING
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

size_t size = 0;
uint8_t outputData[QUEUE_SIZE] = {0};
uint8_t inputData[QUEUE_SIZE] = {0};

typedef struct
{
	uint8_t a;
	uint16_t b;
	uint32_t c;
}	template_t;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
//_____ S T A T I �  F U N C T I O N   D E F I N I T I O N   __________________________________
static bool compare_uint8(const void* cmp1, const void* cmp2)
{
	uint8_t* pCmp1 = (uint8_t*)cmp1;
	uint8_t* pCmp2 = (uint8_t*)cmp2;

	if(*pCmp1 != *pCmp2) {
		return false;
	}

	return true;
}

static bool compare_uint16(const void* cmp1, const void* cmp2)
{
	uint16_t* pCmp1 = (uint16_t*)cmp1;
	uint16_t* pCmp2 = (uint16_t*)cmp2;

	if(*pCmp1 != *pCmp2) {
		return false;
	}

	return true;
}

static bool compare_uint32(const void* cmp1, const void* cmp2)
{
	uint32_t* pCmp1 = (uint32_t*)cmp1;
	uint32_t* pCmp2 = (uint32_t*)cmp2;

	if(*pCmp1 != *pCmp2) {
		return false;
	}

	return true;
}

static bool compare_template_t(const void* cmp1, const void* cmp2)
{
	template_t* pCmp1 = (template_t*)cmp1;
	template_t* pCmp2 = (template_t*)cmp2;
	size_t i = 0;

	if(pCmp1->a == pCmp2->a) {
		i++;
	}

	if(pCmp1->b == pCmp2->b) {
		i++;
	}

	if(pCmp1->c == pCmp2->c) {
		i++;
	}

	return (i == 3) ? true : false;
}


static void preparation_uint8(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
}

static void preparation_uint16(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint16_t));
}

static void preparation_uint32(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint32_t));
}

static void preparation_struct(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(template_t));
}


static void destroy(void **state)
{
	queue_delete(&queue);
}





static void queue_creation_test(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);

	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
	assert_int_not_equal(queue, NULL);

	queue_delete(&queue);
}

static void queue_setup_cb_fail_test(void **state)
{
	expect_assert_failure(queue_reg_mem_alloc_cb(NULL));
	expect_assert_failure(queue_reg_mem_free_cb(NULL));	
}

static void queue_enqueue_fail_test(void **state)
{
	uint8_t i = 0;

	expect_assert_failure(queue_enqueue(NULL, &i));
	expect_assert_failure(queue_enqueue(queue, NULL));
}

static void queue_uint8_enqueue_test(void **state)
{
	uint8_t data = 0x55;
	assert_true(queue_enqueue(queue, &data));
}

static void queue_uint16_enqueue_test(void **state)
{
	uint16_t data = 0x5555;
	assert_true(queue_enqueue(queue, &data));
}

static void queue_uint32_enqueue_test(void **state)
{
	uint32_t data = 0x55555555;
	assert_true(queue_enqueue(queue, &data));
}


static void queue_struct_enqueue_test(void **state)
{
	template_t data = {.a = 10, .b = 100, .c = 1000};
	assert_true(queue_enqueue(queue, &data));
}



static void queue_denqueue_fail_test(void **state)
{
	uint8_t i = 0;

	expect_assert_failure(queue_denqueue(NULL, &i));
	expect_assert_failure(queue_denqueue(queue, NULL));
}

static void queue_uint8_denqueue_test(void **state)
{
	uint8_t expected_data = 0x55;
	uint8_t readed_data = 0;

	queue_enqueue(queue, &expected_data);
	assert_true(queue_denqueue(queue, &readed_data));
	assert_int_equal(readed_data, expected_data);
}

static void queue_uint16_denqueue_test(void **state)
{
	uint16_t expected_data = 0x5555;
	uint16_t readed_data = 0;

	queue_enqueue(queue, &expected_data);
	assert_true(queue_denqueue(queue, &readed_data));
	assert_int_equal(readed_data, expected_data);
}

static void queue_uint32_denqueue_test(void **state)
{
	uint32_t expected_data = 0x55555555;
	uint32_t readed_data = 0;

	queue_enqueue(queue, &expected_data);
	assert_true(queue_denqueue(queue, &readed_data));
	assert_int_equal(readed_data, expected_data);
}


static void queue_struct_denqueue_test(void **state)
{
	template_t expected_data = {.a = 10, .b = 100, .c = 1000};
	template_t readed_data = {0};

	queue_enqueue(queue, &expected_data);
	assert_true(queue_denqueue(queue, &readed_data));
	assert_memory_equal(&expected_data, &readed_data, sizeof(template_t));
}


static void queue_low_border_test(void **state)
{
	uint8_t data = 0;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
	assert_false(queue_denqueue(queue, &data));
	queue_delete(&queue);
}

static void queue_high_border_test(void **state)
{
	uint8_t data = 0;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));

	for(uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		queue_enqueue(queue, &i);
	}

	assert_false(queue_enqueue(queue, &data));
	queue_delete(&queue);
}


static void queue_empty_test(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));
	assert_true(queue_is_empty(queue));
	queue_delete(&queue);
}

static void queue_full_test(void **state)
{
	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));

	for(uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		queue_enqueue(queue, &i);
	}

	assert_true(queue_is_full(queue));
	queue_delete(&queue);
}


static void queue_size_test(void **state)
{
	size_t size = 0;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));

	for(uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		size = queue_size(queue);
		assert_int_equal(size, i);
		queue_enqueue(queue, &i);
	}

	queue_delete(&queue);
}


static void queue_size_uint16_test(void **state)
{
	size_t size = 0;
	size_t cap = 0;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint16_t));
	cap = queue_free_space(queue);

	for(uint16_t i = 0; i < cap; i++)
	{
		size = queue_size(queue);
		assert_int_equal(size, i);
		queue_enqueue(queue, &i);
	}

	queue_delete(&queue);
}


static void queue_free_space_test(void **state)
{
	size_t size = 0;
	size_t fspace = QUEUE_SIZE;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));

	for(uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		size = queue_free_space(queue);
		assert_int_equal(size, fspace);
		queue_enqueue(queue, &i);
		fspace--;
	}

	queue_delete(&queue);
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


static void queue_uint8_find_test(void **state)
{
	uint8_t data = 0;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint8_t));

	for(uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		queue_enqueue(queue, &i);
	}

	assert_true(queue_find(queue, &data, compare_uint8));

	data = QUEUE_SIZE - 1;
	assert_true(queue_find(queue, &data, compare_uint8));

	queue_delete(&queue);
}

static void queue_uint16_find_test(void **state)
{
	uint16_t data = 0;
	size_t size = 0;
	size_t fsize = 0;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint16_t));

	fsize = queue_free_space(queue);

	for(uint16_t i = 0; i < fsize; i++)
	{
		queue_enqueue(queue, &i);
	}

	size = queue_size(queue);

	assert_true(queue_find(queue, &data, compare_uint16));

	data = size - 1;
	assert_true(queue_find(queue, &data, compare_uint16));

	queue_delete(&queue);
}

static void queue_uint32_find_test(void **state)
{
	uint32_t data = 0;
	size_t size = 0;

	queue_reg_mem_alloc_cb(&malloc);
	queue_reg_mem_free_cb(&free);
	queue = queue_create(QUEUE_SIZE, sizeof(uint32_t));

	size = queue_free_space(queue);
	for(uint32_t i = 0; i < size; i++)
	{
		queue_enqueue(queue, &i);
	}

	assert_true(queue_find(queue, &data, compare_uint32));

	data = size - 1;
	assert_true(queue_find(queue, &data, compare_uint32));

	queue_delete(&queue);
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
		  unit_test(queue_setup_cb_fail_test),
		  unit_test(queue_creation_test),
		  unit_test(queue_enqueue_fail_test),
		  unit_test_setup_teardown(queue_uint8_enqueue_test, preparation_uint8, destroy),
		  unit_test_setup_teardown(queue_uint16_enqueue_test, preparation_uint16, destroy),
		  unit_test_setup_teardown(queue_uint32_enqueue_test, preparation_uint32, destroy),
		  unit_test_setup_teardown(queue_struct_enqueue_test, preparation_struct, destroy),
		  unit_test(queue_denqueue_fail_test),
		  unit_test_setup_teardown(queue_uint8_denqueue_test, preparation_uint8, destroy),
		  unit_test_setup_teardown(queue_uint16_denqueue_test, preparation_uint16, destroy),
		  unit_test_setup_teardown(queue_uint32_denqueue_test, preparation_uint32, destroy),
		  unit_test_setup_teardown(queue_struct_denqueue_test, preparation_struct, destroy),
		  unit_test(queue_low_border_test),
		  unit_test(queue_high_border_test),
		  unit_test(queue_empty_test),
		  unit_test(queue_full_test),
		  unit_test(queue_size_test),
		  unit_test(queue_size_uint16_test),
		  unit_test(queue_free_space_test),
		  unit_test_setup_teardown(queue_peek_test, preparation_uint8, destroy),
		  unit_test_setup_teardown(queue_flush_test, preparation_uint8, destroy),
		  unit_test(queue_uint8_find_test),
		  unit_test(queue_uint16_find_test),
		  unit_test(queue_uint32_find_test),
  };

  run_tests(tests);
}
