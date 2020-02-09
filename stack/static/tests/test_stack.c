// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**********************************************************************************************
* @file    		QAdfifo.c
* @author  		Kovalchuk Alexander aka mz4
* @email 		roux@yandex.ru
* @version 		0.1
* @date    		06.06.2018
* @brief		Functions for testing dfifo library.
***********************************************************************************************/
//_____ I N C L U D E S _______________________________________________________________________
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stack.h"
#include "QAstack.h"
#include "cmockery.h"
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________________________
static stack_t tstStack;
static stackData_t outputData[STACK_MAX_SIZE] = {0};
static stackData_t inputData[STACK_MAX_SIZE] = {0};
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

	assert_true(stack_init(&tstStack));
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
static void stack_main_test(void **state)
{
//	for(size_t i = 0; i < sizeof(inputData); i++) {
//		assert_true(lfifo_enqueue(tstFifo, inputData[i]));
//	}
//
//	for(size_t i = 0; i < sizeof(outputData); i++) {
//		assert_true(lfifo_denqueue(tstFifo, &outputData[i]));
//	}
//
//	assert_memory_equal(inputData, outputData, SFIFO_LENGTH);
}
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________________________
void stack_test(void)
{
  const UnitTest tests[] = {
		  unit_test_setup_teardown(stack_main_test, preparation_data, destroy_data),
  };

  run_tests(tests);
}
