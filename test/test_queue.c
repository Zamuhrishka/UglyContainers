#include "unity.h"
#include "queue.h"
#include "custom_allocator.h"
#include <stdlib.h>

#define POOL_SIZE_IN_BYTES			100

static queue_t* queue = NULL;

void setUp(void)
{
#if 1
    queue_reg_mem_alloc_cb(malloc);
	queue_reg_mem_free_cb(free); 
#else

	queue_reg_mem_alloc_cb(static_malloc);
	queue_reg_mem_free_cb(static_free); 
#endif
}

void tearDown(void)
{
}

void test_create(void)
{    
	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t));   
	TEST_ASSERT_NOT_NULL(queue);

	queue_delete(&queue);
}

void test_enqueue(void)
{
	uint8_t data = 0x55;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 
	TEST_ASSERT_TRUE(queue_enqueue(queue, &data));

	queue_delete(&queue);
}

void test_enqueue16(void)
{
	uint16_t data = 0x5555;

	queue_t* queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint16_t));
	TEST_ASSERT_TRUE(queue_enqueue(queue, &data));

	queue_delete(&queue);
}

void test_enqueue32(void)
{
	uint32_t data = 0x55555555;

	queue_t* queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint32_t));
	TEST_ASSERT_TRUE(queue_enqueue(queue, &data));

	queue_delete(&queue);
}

void test_denqueue(void)
{
	uint8_t expected_data = 0x55;
	uint8_t readed_data = 0;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 

	queue_enqueue(queue, &expected_data);
	TEST_ASSERT_TRUE(queue_denqueue(queue, &readed_data));
	TEST_ASSERT_EQUAL_INT(readed_data, expected_data);

	queue_delete(&queue);
}

void test_denqueue16(void)
{
	uint16_t expected_data = 0x5555;
	uint16_t readed_data = 0;

	queue_t* queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint16_t));

	queue_enqueue(queue, &expected_data);
	TEST_ASSERT_TRUE(queue_denqueue(queue, &readed_data));
	TEST_ASSERT_EQUAL_INT(readed_data, expected_data);

	queue_delete(&queue);
}

void test_denqueue32(void)
{
	uint32_t expected_data = 0x55555555;
	uint32_t readed_data = 0;

	queue_t* queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint32_t));

	queue_enqueue(queue, &expected_data);
	TEST_ASSERT_TRUE(queue_denqueue(queue, &readed_data));
	TEST_ASSERT_EQUAL_INT(readed_data, expected_data);

	queue_delete(&queue);
}

void test_low_border(void)
{
	uint8_t data = 0;    

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 
	TEST_ASSERT_FALSE(queue_denqueue(queue, &data));

	queue_delete(&queue);
}

void test_high_border(void)
{
	uint8_t data = 0;
    size_t i = 0;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 

	for(i = 0; i < POOL_SIZE_IN_BYTES/sizeof(uint8_t); i++) {
		TEST_ASSERT_TRUE(queue_enqueue(queue, (uint8_t*)&i));
	}

	TEST_ASSERT_FALSE(queue_enqueue(queue, &data));

	queue_delete(&queue);
}

void test_empty(void)
{
	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 	
	TEST_ASSERT_TRUE(queue_is_empty(queue));

	queue_delete(&queue);
}

void test_full(void)
{
    size_t i = 0;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 

	for(i = 0; i < POOL_SIZE_IN_BYTES/sizeof(uint8_t); i++) {
		TEST_ASSERT_TRUE(queue_enqueue(queue, (uint8_t*)&i));
	}

	TEST_ASSERT_TRUE(queue_is_full(queue));

	queue_delete(&queue);
}

void test_size(void)
{
	size_t size = 0;
    size_t i = 0;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 

	for(i = 0; i < POOL_SIZE_IN_BYTES/sizeof(uint8_t); i++)
	{
		size = queue_size(queue);
		TEST_ASSERT_EQUAL_INT(size, i);
		TEST_ASSERT_TRUE(queue_enqueue(queue, (uint8_t*)&i));
	}

	queue_delete(&queue);
}

void test_queue_free_space(void)
{
	size_t size = 0;
	size_t fspace = POOL_SIZE_IN_BYTES/sizeof(uint8_t);
    size_t i = 0;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 

	for(i = 0; i < POOL_SIZE_IN_BYTES/sizeof(uint8_t); i++)
	{
		size = queue_free_space(queue);
		TEST_ASSERT_EQUAL_INT(size, fspace);
		queue_enqueue(queue, (uint8_t*)&i);
		fspace--;
	}

	queue_delete(&queue);
}

void test_peek(void)
{
	size_t size = 0;
	uint8_t tmpData = 0;
	uint8_t data[POOL_SIZE_IN_BYTES/sizeof(uint8_t)];
    size_t i = 0;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 

	size = queue_free_space(queue);

	for(i = 0; i < size; i++) {
		data[i] = i;
	}

	for(i = 0; i < size; i++) {
		TEST_ASSERT_TRUE(queue_enqueue(queue, &data[i]));
	}

	TEST_ASSERT_TRUE(queue_peek(queue, &tmpData));
	TEST_ASSERT_EQUAL_INT(queue_size(queue), POOL_SIZE_IN_BYTES/sizeof(uint8_t));

	TEST_ASSERT_TRUE(queue_peek(queue, &tmpData));
	TEST_ASSERT_EQUAL_INT(queue_size(queue), POOL_SIZE_IN_BYTES/sizeof(uint8_t));

	queue_delete(&queue);
}

void test_reset(void)
{
	size_t size = 0;
	uint8_t tmpData = 0;
	uint8_t data[POOL_SIZE_IN_BYTES/sizeof(uint8_t)];
    size_t i = 0;

	queue = queue_create(POOL_SIZE_IN_BYTES, sizeof(uint8_t)); 
    
	size = queue_free_space(queue);

	for(i = 0; i < size; i++) {
		data[i] = i;
	}

	for(i = 0; i < size; i++) {
		TEST_ASSERT_TRUE(queue_enqueue(queue, &data[i]));
	}

	TEST_ASSERT_EQUAL_INT(queue_size(queue), size);

	queue_reset(queue);
	TEST_ASSERT_EQUAL_INT(queue_size(queue), 0);
	TEST_ASSERT_TRUE(queue_is_empty(queue));

	TEST_ASSERT_FALSE(queue_denqueue(queue, &tmpData));
}