/**********************************************************************************************
* @file    		QAdfifo.c
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @version 		0.1
* @date    		06.06.2018
* @brief		Functions for testing dfifo library.
***********************************************************************************************/
//_____ I N C L U D E S _______________________________________________________________________
#include "QAvector.h"
#include "vector.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "cmockery.h"
#ifdef DEBUG
	#include "debug.h"
#endif
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
static vector_t* tstVector;
static vDataType_t outputData[250] = {0};
static vDataType_t inputData[250] = {0};
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
//_____ S T A T I Ñ  F U N C T I O N   D E F I N I T I O N   __________________________________
/**
* @brief 	Unit testing Setup function.
*
* @param  	none.
*
* @return 	none.
*/
static void preparation_data(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = i;
	}

	vector_alloc_callback_reg(&malloc);
	vector_free_callback_reg(&free);

	tstVector = vector_create(sizeof(inputData));
	assert_int_not_equal(tstVector, NULL);
}

/**
* @brief 	Unit testing TearsDown function.
*
* @param  	none.
*
* @return 	none.
*/
static void destroy_data(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = 0;
	}

	for(size_t i = 0; i < sizeof(outputData); i++) {
		outputData[i] = 0;
	}

	vector_delete(&tstVector);
}


static void QAvector_critical_func_testing(void **state)
{
	vector_t* vector = NULL;;
	tstVector = vector_create(sizeof(inputData));
	assert_int_equal(vector, NULL);
}


/**
* @brief 	Testing main functions of fifo.
*
* @details	Testing next functions:
*			- creating new fifo;
*			- enqueue data into fifo;
*			- denqueue data from fifo;
*
* @param  	*inputData[in] - pointer to the input data array which will be enqueue into fifo.
* @param	*outputData[out] - pointer to the out data array in which will be store data from fifo.
* @param	size[in] - size of unput/output data arrays.
*
* @return 	true/false.
*/
static void QAvector_pop_front_func_testing(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	for(size_t i = 0; i < sizeof(outputData); i++) {
		assert_true(vector_pop_front(tstVector, &outputData[i]));
	}

	assert_memory_equal(inputData, outputData, sizeof(inputData));
}


static void QAvector_pop_back_func_testing(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	for(size_t i = sizeof(outputData); i > 0 ; i--) {
		assert_true(vector_pop_back(tstVector, &outputData[i-1]));
	}

	assert_memory_equal(inputData, outputData, sizeof(inputData));
}

static void QAvector_at_func_testing(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	for(size_t i = sizeof(outputData); i > 0 ; i--) {
		assert_true(vector_at(tstVector, &outputData[i], i));
	}

	assert_memory_equal(inputData, outputData, sizeof(inputData));
}


static void QAvector_extract_func_testing(void **state)
{
	vDataType_t data = 0;

	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	assert_true(vector_extract(tstVector, &data, sizeof(inputData)/2));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) - 1);
	assert_int_equal(data, sizeof(inputData)/2);

	assert_true(vector_extract(tstVector, &data, 0));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) - 2);
	assert_int_equal(data, 0);

	assert_true(vector_extract(tstVector, &data, sizeof(inputData) - 3));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) - 3);
	assert_int_equal(data, sizeof(inputData) - 1);
}


static void QAvector_insert_func_testing(void **state)
{
	vDataType_t data = 0;

	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	assert_true(vector_insert(tstVector, 0x13, sizeof(inputData)/2));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) + 1);
	assert_true(vector_at(tstVector, &data, sizeof(inputData)/2));
	assert_int_equal(data, 0x13);

	assert_true(vector_insert(tstVector, 0x13, 0));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) + 2);
	assert_true(vector_at(tstVector, &data, 0));
	assert_int_equal(data, 0x13);

	assert_true(vector_insert(tstVector, 0x13, sizeof(inputData) + 2));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) + 3);
	assert_true(vector_at(tstVector, &data, sizeof(inputData) + 2));
	assert_int_equal(data, 0x13);
}

static void QAvector_size_func_testing(void **state)
{
	assert_true(vector_empty(tstVector));

	for(size_t i = 0; i < sizeof(inputData); i++)
	{
		assert_int_equal(vector_size(tstVector), i);
		assert_true(vector_append(tstVector, inputData[i]));
		assert_false(vector_empty(tstVector));
	}

	assert_int_equal(vector_capacity(tstVector), sizeof(inputData) + RESIZE_KOEFF);
}

static void QAvector_resize_func_testing(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	assert_int_equal(vector_size(tstVector), sizeof(inputData));

	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	assert_int_equal(vector_size(tstVector), sizeof(inputData) * 2);
}


static void QAvector_clear_func_testing(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	assert_true(vector_clear(tstVector));
	assert_int_equal(vector_size(tstVector), 0);
}


static void QAvector_erase_func_testing(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(vector_append(tstVector, inputData[i]));
	}

	assert_true(vector_erase(tstVector, sizeof(inputData)/2));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) - 1);

	assert_true(vector_erase(tstVector, 0));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) - 2);

	assert_true(vector_erase(tstVector,sizeof(inputData) - 3));
	assert_int_equal(vector_size(tstVector), sizeof(inputData) - 3);
}


static void QAvector_fail_func_testing(void **state)
{
	vDataType_t data = 0;

	assert_false(vector_at(tstVector, &data, 0));
	assert_false(vector_at(tstVector, &data, sizeof(inputData)));

	assert_false(vector_pop_back(tstVector, &data));
	assert_false(vector_pop_front(tstVector, &data));
	assert_false(vector_erase(tstVector, 2));

	assert_false(vector_extract(tstVector, &data, 0));
	assert_false(vector_extract(tstVector, &data, sizeof(inputData)));
}

//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
void vector_test(void)
{
  const UnitTest tests[] = {
		  unit_test(QAvector_critical_func_testing),
		  unit_test_setup_teardown(QAvector_pop_front_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_pop_back_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_at_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_extract_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_insert_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_size_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_resize_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_clear_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_erase_func_testing, preparation_data, destroy_data),
		  unit_test_setup_teardown(QAvector_fail_func_testing, preparation_data, destroy_data),
  };

  run_tests(tests);
}
