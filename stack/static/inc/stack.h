/**********************************************************************************************
* @file    		stack.h
* @author  		learnc.info@gmail.com
* @website		https://learnc.info/adt/stack.html
* @correct 		alexander.kovalchuk@promwad.com
* @brief		Стек фиксированного размера, построенный на массиве
***********************************************************************************************/
#pragma once
/* C++ detection */
#ifdef __cplusplus
	extern "C" {
#endif
//_____ I N C L U D E S _______________________________________________________
#include "stdlib.h"
#include "stdbool.h"
#include "stdint.h"
//_____ С O N F I G S__________________________________________________________
#define STACK_MAX_SIZE 									(32ul)
typedef uint8_t 										stackData_t;
//_____ M A C R O S ___________________________________________________________
//_____ D E F I N I T I O N ___________________________________________________
//_____ V A R I A B L E   D E C L A R A T I O N S _____________________________
typedef struct
{
	stackData_t data[STACK_MAX_SIZE];
    size_t size;
} 	stack_t;
//_____ F U N C T I O N   D E C L A R A T I O N S _____________________________
/**
* @brief 	Init stack.
*
* @param  	stack[in] - pointer to stack.
*
* @return 	true/false.
*/
bool stack_init(stack_t *stack);

/**
* @brief 	Push data into stack.
*
* @param  	stack[in] - pointer to stack.
* @param  	value[in] - value for saving in to stack.
*
* @return 	true/false.
*/
bool stack_push(stack_t *stack, const stackData_t value);

/**
* @brief 	Pop data from stack.
*
* @param  	stack[in] - pointer to stack.
* @param  	value[out] - pointer to value.
*
* @return 	true/false.
*/
bool stack_pop(stack_t *stack, stackData_t *value);

/**
* @brief 	Return value on top of stack but not delete it.
*
* @param  	stack[in] - pointer to stack.
* @param  	value[out] - pointer to value.
*
* @return 	STACK_NO_ERR - if push was ok.
* 		  	STACK_UNDERFLOW_ERR - stack underflow error occur.
*/
bool stack_peek(const stack_t *stack, stackData_t *value);

/**
* @brief 	Return value quantity data of stack.
*
* @param  	*stack[in] - pointer to stack.
*
* @return 	quantity of data.
*/
size_t stack_get_size(const stack_t *stack);

/* C++ detection */
#ifdef __cplusplus
}
#endif
