/**********************************************************************************************
* @file    		QAdfifo.c
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @version 		0.1
* @date    		06.06.2018
* @brief		Functions for testing dfifo library.
***********************************************************************************************/
//_____ I N C L U D E S _______________________________________________________________________
#include "uqueue.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "cmockery.h"
#ifdef DEBUG
	#include "debug.h"
#endif
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
#define QUEUE_SIZE			32
#define BUFFER_SIZE			22

uqueue_t* uqueue = NULL;

typedef struct
{
	uint8_t a;
	uint16_t b;
	uint32_t c;
}	template_t;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
//_____ S T A T I Ñ  F U N C T I O N   D E F I N I T I O N   __________________________________
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


static void preparation_data(void **state)
{

}
static void destroy_data(void **state)
{
	uqueue_delete(&uqueue);
}

static void uqueue_uint8_main_test(void **state)
{
	uint8_t outputData[QUEUE_SIZE] = {0};
	uint8_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint8_t) * QUEUE_SIZE, sizeof(uint8_t), compare_uint8);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);
	assert_memory_equal(inputData, outputData, QUEUE_SIZE);
}

static void uqueue_uint8_unique_test(void **state)
{
	uint8_t outputData[QUEUE_SIZE] = {0};
	uint8_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE/2; i++) {
		inputData[i] = i;
	}

	for(size_t i = QUEUE_SIZE/2; i < QUEUE_SIZE; i++) {
		inputData[i] = inputData[i - QUEUE_SIZE/2];
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint8_t) * QUEUE_SIZE, sizeof(uint8_t), compare_uint8);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE/2);

	for(size_t i = 0; i < QUEUE_SIZE/2; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);
	assert_memory_equal(inputData, outputData, QUEUE_SIZE/2);
}


static void uqueue_uint16_main_test(void **state)
{
	uint16_t outputData[QUEUE_SIZE] = {0};
	uint16_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint16_t) * QUEUE_SIZE, sizeof(uint16_t), compare_uint16);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);
	assert_memory_equal(inputData, outputData, QUEUE_SIZE);
}

static void uqueue_uint16_unique_test(void **state)
{
	uint16_t outputData[QUEUE_SIZE] = {0};
	uint16_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE/2; i++) {
		inputData[i] = i;
	}

	for(size_t i = QUEUE_SIZE/2; i < QUEUE_SIZE; i++) {
		inputData[i] = inputData[i - QUEUE_SIZE/2];
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint16_t) * QUEUE_SIZE, sizeof(uint16_t), compare_uint16);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE/2);

	for(size_t i = 0; i < QUEUE_SIZE/2; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);
	assert_memory_equal(inputData, outputData, QUEUE_SIZE/2);
}

static void uqueue_uint32_main_test(void **state)
{
	uint32_t outputData[QUEUE_SIZE] = {0};
	uint32_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		inputData[i] = i;
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint32_t) * QUEUE_SIZE, sizeof(uint32_t), compare_uint32);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);
	assert_memory_equal(inputData, outputData, QUEUE_SIZE);
}

static void uqueue_uint32_unique_test(void **state)
{
	uint32_t outputData[QUEUE_SIZE] = {0};
	uint32_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE/2; i++) {
		inputData[i] = i;
	}

	for(size_t i = QUEUE_SIZE/2; i < QUEUE_SIZE; i++) {
		inputData[i] = inputData[i - QUEUE_SIZE/2];
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint32_t) * QUEUE_SIZE, sizeof(uint32_t), compare_uint32);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE/2);

	for(size_t i = 0; i < QUEUE_SIZE/2; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);
	assert_memory_equal(inputData, outputData, QUEUE_SIZE/2);
}

static void uqueue_struct_main_test(void **state)
{
	template_t outputData[QUEUE_SIZE] = {0};
	template_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		inputData[i].a = i;
		inputData[i].b = i * 100;
		inputData[i].c = i * 100;
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(template_t) * QUEUE_SIZE, sizeof(template_t), compare_template_t);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);

	for(size_t i = 0; i < QUEUE_SIZE/2; i++)
	{
		assert_memory_equal(&inputData[i], &outputData[i], sizeof(template_t));
	}
}

static void uqueue_struct_unique_test(void **state)
{
	template_t outputData[QUEUE_SIZE] = {0};
	template_t inputData[QUEUE_SIZE] = {0};

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		inputData[i].a = i;
		inputData[i].b = i * 100;
		inputData[i].c = i * 100;
	}

	for(size_t i = QUEUE_SIZE/2; i < QUEUE_SIZE; i++) {
		inputData[i] = inputData[i - QUEUE_SIZE/2];
	}

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(template_t) * QUEUE_SIZE, sizeof(template_t), compare_template_t);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++)
	{
		assert_true(uqueue_enqueue(uqueue, &inputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE/2);

	for(size_t i = 0; i < QUEUE_SIZE/2; i++)
	{
		assert_true(uqueue_denqueue(uqueue, &outputData[i]));
	}

	assert_int_equal(uqueue_size(uqueue), 0);

	for(size_t i = 0; i < QUEUE_SIZE/2; i++)
	{
		assert_memory_equal(&inputData[i], &outputData[i], sizeof(template_t));
	}
}

static void uqueue_empty_denqueue_test(void **state)
{
	uint8_t tmpData = 0;

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint8_t) * QUEUE_SIZE, sizeof(uint8_t), compare_uint8);
	assert_int_not_equal(uqueue, NULL);

	assert_false(uqueue_denqueue(uqueue, &tmpData));
}

static void uqueue_full_enqueue_test(void **state)
{
	uint8_t data[QUEUE_SIZE];

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint8_t) * QUEUE_SIZE, sizeof(uint8_t), compare_uint8);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		data[i] = i;
	}

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		assert_true(uqueue_enqueue(uqueue, &data[i]));
	}

	assert_false(uqueue_enqueue(uqueue, &data[0]));
}

static void uqueue_peek_test(void **state)
{
	uint8_t tmpData = 0;
	uint8_t data[QUEUE_SIZE];

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint8_t) * QUEUE_SIZE, sizeof(uint8_t), compare_uint8);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		data[i] = i;
	}

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		assert_true(uqueue_enqueue(uqueue, &data[i]));
	}

	assert_true(uqueue_peek(uqueue, &tmpData));
	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE);

	assert_true(uqueue_peek(uqueue, &tmpData));
	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE);
}

static void uqueue_flush_test(void **state)
{
	uint8_t tmpData = 0;
	uint8_t data[QUEUE_SIZE];

	uqueue_reg_mem_alloc_cb(&malloc);
	uqueue_reg_mem_free_cb(&free);

	uqueue = uqueue_create(sizeof(uint8_t) * QUEUE_SIZE, sizeof(uint8_t), compare_uint8);
	assert_int_not_equal(uqueue, NULL);

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		data[i] = i;
	}

	for(size_t i = 0; i < QUEUE_SIZE; i++) {
		assert_true(uqueue_enqueue(uqueue, &data[i]));
	}

	assert_int_equal(uqueue_size(uqueue), QUEUE_SIZE);

	uqueue_flush(uqueue);
	assert_int_equal(uqueue_size(uqueue), 0);

	assert_false(uqueue_denqueue(uqueue, &tmpData));
}
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
void uqueue_test(void)
{
  const UnitTest tests[] =
  {
		  unit_test_setup_teardown(preparation_data, uqueue_uint8_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_uint8_unique_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_uint16_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_uint16_unique_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_uint32_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_uint32_unique_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_struct_main_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_struct_unique_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_empty_denqueue_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_full_enqueue_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_peek_test, destroy_data),
		  unit_test_setup_teardown(preparation_data, uqueue_flush_test, destroy_data),
  };

  run_tests(tests);
}
