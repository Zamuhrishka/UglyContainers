/**********************************************************************************************
* @file    		stack.c
* @author  		learnc.info@gmail.com
* @website		https://learnc.info/adt/stack.html
* @correct 		alexander.kovalchuk@promwad.com
* @brief		Стек фиксированного размера, построенный на массиве
***********************************************************************************************/
//_____ I N C L U D E S _______________________________________________________
#include "stack.h"
#include "stdbool.h"
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________
//_____ S T A T I С  F U N C T I O N   D E F I N I T I O N   __________________
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________
/**
* @brief 	Init stack.
*
* @param  	stack[in] - pointer to stack.
*
* @return 	true/false.
*/
bool stack_init(stack_t *stack)
{
	stack->size = 0;
	return true;
}

/**
* @brief 	Push data into stack.
*
* @param  	stack[in] - pointer to stack.
* @param  	value[in] - value for saving in to stack.
*
* @return 	true/false.
*/
bool stack_push(stack_t *stack, const stackData_t value)
{
    if (stack->size >= STACK_MAX_SIZE) {
        return false;
    }

    stack->data[stack->size] = value;
    stack->size++;

    return true;
}

/**
* @brief 	Pop data from stack.
*
* @param  	stack[in] - pointer to stack.
* @param  	value[out] - pointer to value.
*
* @return 	true/false.
*/
bool stack_pop(stack_t *stack, stackData_t *value)
{
    if (stack->size == 0) {
        return false;
    }

    stack->size--;
    *value = stack->data[stack->size];

    return true;
}

/**
* @brief 	Return value on top of stack but not delete it.
*
* @param  	stack[in] - pointer to stack.
* @param  	value[out] - pointer to value.
*
* @return 	true/false.
*/
bool stack_peek(const stack_t *stack, stackData_t *value)
{
    if (stack->size <= 0) {
        return false;
    }

    *value = stack->data[stack->size];

    return true;
}

/**
* @brief 	Return value quantity data of stack.
*
* @param  	*stack[in] - pointer to stack.
*
* @return 	quantity of data.
*/
size_t stack_get_size(const stack_t *stack)
{
	return stack->size;
}
