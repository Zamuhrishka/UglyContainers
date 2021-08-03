#include "unity.h"
#include "vector.h"
#include <stdlib.h>

static vector_t* tstVector;
static uint8_t outputData[250] = {0};
static uint8_t inputData[250] = {0};

void setUp(void)
{
    for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = i;
	}

	for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = 0;
	}

    vector_reg_mem_alloc_cb(malloc);
	vector_reg_mem_free_cb(free); 
}

void tearDown(void)
{
    for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = 0;
	}

	for(size_t i = 0; i < sizeof(outputData); i++) {
		outputData[i] = 0;
	}
}

void test_Create(void)
{
	tstVector = vector_create(sizeof(inputData), sizeof(inputData[0]));
    TEST_ASSERT_NOT_NULL(tstVector);
    vector_delete(&tstVector);
}

void test_PopFront(void)
{
    tstVector = vector_create(sizeof(inputData), sizeof(inputData[0]));

	for(size_t i = 0; i < sizeof(inputData); i++) {
		TEST_ASSERT_TRUE(vector_append(tstVector, (void*)&inputData[i]));
	}

	for(size_t i = 0; i < sizeof(outputData); i++) {
		TEST_ASSERT_TRUE(vector_pop_front(tstVector, (void*)&outputData[i]));
	}

	TEST_ASSERT_EQUAL_MEMORY(inputData, outputData, sizeof(inputData));
}

void test_PopBack(void)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		TEST_ASSERT_TRUE(vector_append(tstVector, (void*)&inputData[i]));
	}

	for(size_t i = sizeof(outputData); i > 0 ; i--) {
		TEST_ASSERT_TRUE(vector_pop_back(tstVector, (void*)&outputData[i-1]));
	}

	TEST_ASSERT_EQUAL_MEMORY(inputData, outputData, sizeof(inputData));
}

void test_At(void)
{
    tstVector = vector_create(sizeof(inputData), sizeof(inputData[0]));

	for(size_t i = 0; i < sizeof(inputData); i++) {
		TEST_ASSERT_TRUE(vector_append(tstVector, (void*)&inputData[i]));
	}

	for(size_t i = sizeof(outputData); i > 0 ; i--) {
		TEST_ASSERT_TRUE(vector_at(tstVector, (void*)&outputData[i], i));
	}

	TEST_ASSERT_EQUAL_MEMORY(inputData, outputData, sizeof(inputData));

    vector_delete(&tstVector);
}

void test_Extract(void)
{
	TEST_IGNORE();
#if 0
	uint8_t data = 0;

	tstVector = vector_create(sizeof(inputData), sizeof(inputData[0]));

	for(size_t i = 0; i < sizeof(inputData); i++) {
		TEST_ASSERT_TRUE(vector_append(tstVector, (void*)&inputData[i]));
	}

	uint8_t expected_data = sizeof(inputData)/2;
	TEST_ASSERT_TRUE(vector_extract(tstVector, &data, sizeof(inputData)/2));
	TEST_ASSERT_EQUAL_INT(vector_size(tstVector), sizeof(inputData) - 1);
	TEST_ASSERT_EQUAL_INT(data, expected_data);

	// TEST_ASSERT_TRUE(vector_extract(tstVector, &data, 0));
	// TEST_ASSERT_EQUAL_INT(vector_size(tstVector), sizeof(inputData) - 2);
	// TEST_ASSERT_EQUAL_INT(data, 0);

	// TEST_ASSERT_TRUE(vector_extract(tstVector, &data, sizeof(inputData) - 3));
	// TEST_ASSERT_EQUAL_INT(vector_size(tstVector), sizeof(inputData) - 3);
	// TEST_ASSERT_EQUAL_INT(data, sizeof(inputData));
#endif
}






