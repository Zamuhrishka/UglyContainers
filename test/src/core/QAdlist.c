/**********************************************************************************************
* @file    		QAlist.c
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @version 		0.1
* @date    		06.06.2018
* @brief		Functions for testing single-linked list library.
***********************************************************************************************/
//_____ I N C L U D E S _______________________________________________________________________
#include <dlist.h>
#include <QAdlist.h>
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "cmockery.h"
//_____ D E F I N I T I O N ___________________________________________________________________
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
static dLinkedList_t* tstList;
static dListData_t inputData[5] = {0};
static dListData_t outputData[5] = {0};
static dListData_t tstValue = 0;
static dListData_t expectSum = 0;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________________________
/**
* @brief 	Calculate crc16 checksum.
*
* @param  	*data[in] - array of data.
* @param  	len[in] - lenth of data.
*
* @return 	checksum.
*/
inline static void array_reverse(uint8_t *array, size_t nbm)
{
	for(uint8_t i=0; i <nbm/2; i++)
	{
		uint8_t tmp = array[i];
		array[i] = array[nbm-i-1];
		array[nbm-i-1] = tmp;
	}
}
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

	dlist_alloc_callback_reg(&malloc);
	dlist_free_callback_reg(&free);

	tstList = dlist_create();
	assert_true(tstList);
}

/**
* @brief 	Unit testing Setup function.
*
* @param  	none.
*
* @return 	none.
*/
static void preparation_and_fill_data(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = i;
	}

	dlist_alloc_callback_reg(&malloc);
	dlist_free_callback_reg(&free);

	tstList = dlist_create();
	assert_true(tstList);

	assert_true(dlist_from_array(tstList, inputData, sizeof(inputData)));
}

/**
* @brief 	Unit testing Setup function.
*
* @param  	none.
*
* @return 	none.
*/
static void preparation_sum_data(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = i;
		expectSum += i;
	}

	dlist_alloc_callback_reg(&malloc);
	dlist_free_callback_reg(&free);

	tstList = dlist_create();
	assert_true(tstList);
	assert_true(dlist_from_array(tstList, inputData, sizeof(inputData)));
}


/**
* @brief 	Unit testing Setup function.
*
* @param  	none.
*
* @return 	none.
*/
static void preparation_count_data(void **state)
{
	for(size_t i = 0; i < sizeof(inputData); i++) {
		inputData[i] = i;
	}

	inputData[10] = 13;
	inputData[111] = 13;
	inputData[222] = 13;
	inputData[57] = 13;
	inputData[187] = 13;
	inputData[247] = 13;

	dlist_alloc_callback_reg(&malloc);
	dlist_free_callback_reg(&free);

	tstList = dlist_create();
	assert_true(tstList);
	assert_true(dlist_from_array(tstList, inputData, sizeof(inputData)));
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

	tstValue = 0;
	expectSum = 0;

	assert_true(dlist_delete(&tstList));
}

/**
* @brief 	Testing creating list from array and save list to array functions.
*
* @details	Testing next functions:
*			- list_from_array();
*			- list_to_array();
*
* @param  	none.
*
* @return 	none.
*/
static void list_array_test(void **state)
{
	assert_true(dlist_from_array(tstList, inputData, sizeof(inputData)));
	assert_true(dlist_to_array(tstList, outputData, sizeof(outputData)));
	assert_memory_equal(inputData, outputData, sizeof(inputData));
}

/**
* @brief 	Testing list push and pop functions.
*
* @details	Testing next functions:
*			- list_push();
*			- list_pop();
*
* @param  	none.
*
* @return 	none.
*/
static void list_push_pull_test(void **state)
{
	assert_false(dlist_push(NULL, inputData[0]));
	assert_false(dlist_pop(NULL, &outputData[0]));
	assert_false(dlist_pop(tstList, &outputData[0]));

	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(dlist_push(tstList, inputData[i]));
	}

	for(size_t i = 0; i < sizeof(outputData); i++) {
		assert_true(dlist_pop(tstList, &outputData[i]));
	}

	array_reverse(outputData, sizeof(outputData));
	assert_memory_equal(inputData, outputData, sizeof(inputData));
}

/**
* @brief 	Testing list enqueue and dequeue functions.
*
* @details	Testing next functions:
*			- list_enqueue();
*			- list_dequeue();
*
* @param  	none.
*
* @return 	none.
*/
static void list_enq_deq_test(void **state)
{
	assert_false(dlist_enqueue(NULL, inputData[0]));
	assert_false(dlist_dequeue(NULL, &outputData[0]));
	assert_false(dlist_dequeue(tstList, &outputData[0]));

	for(size_t i = 0; i < sizeof(inputData); i++) {
		assert_true(dlist_enqueue(tstList, inputData[i]));
	}

	for(size_t i = 0; i < sizeof(outputData); i++) {
		assert_true(dlist_dequeue(tstList, &outputData[i]));
	}

	array_reverse(outputData, sizeof(outputData));
	assert_memory_equal(inputData, outputData, sizeof(inputData));
}

/**
* @brief 	Testing list insert and extract functions.
*
* @details	Testing next functions:
*			- list_insert();
*			- list_extract();
*
* @param  	none.
*
* @return 	none.
*/
static void list_ins_ext_test(void **state)
{
	assert_false(dlist_insert(tstList, sizeof(inputData)*2, (sizeof(inputData)-1)));
	assert_false(dlist_extract(tstList, sizeof(inputData)*2, &tstValue));

	assert_true(dlist_insert(tstList, sizeof(inputData), (sizeof(inputData)-1)));
	assert_true(dlist_extract(tstList, sizeof(inputData), &tstValue));
	assert_int_equal((sizeof(inputData)-1), tstValue);

	assert_true(dlist_insert(tstList, 0, 1));
	assert_true(dlist_extract(tstList, 0, &tstValue));
	assert_int_equal(1, tstValue);

	assert_true(dlist_insert(tstList, sizeof(inputData)/2, sizeof(inputData)/2));
	assert_true(dlist_extract(tstList, sizeof(inputData)/2, &tstValue));
	assert_int_equal(sizeof(inputData)/2, tstValue);
}


//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
void dlist_test(void)
{
  const UnitTest tests[] = {
		  unit_test_setup_teardown(list_array_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(list_push_pull_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(list_enq_deq_test, preparation_data, destroy_data),
		  unit_test_setup_teardown(list_ins_ext_test, preparation_and_fill_data, destroy_data),
  };

  run_tests(tests);
}
