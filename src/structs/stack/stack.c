// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
/**
 * @file stack.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "allocator_if.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
stack_t* stack_create(size_t esize)
{
    assert(0 != esize);

    stack_t* stack = container_create(esize, CONTAINER_VECTOR_BASED);
    if (NULL == stack)
    {
        return NULL;
    }

    return stack;
}

void stack_delete(stack_t** stack)
{
    assert(*stack);
    assert(stack);

    container_delete((container_t**)stack);
}

bool stack_push(stack_t* stack, const void* data)
{
    assert(NULL != stack);
    assert(NULL != data);

    return container_push_back((container_t*)stack, data);
}

bool stack_pop(stack_t* stack, void* data)
{
    assert(NULL != stack);
    assert(NULL != data);

    return container_pop_back((container_t*)stack, data);
}

bool stack_peek(const stack_t* stack, void* data)
{
    assert(NULL != stack);
    assert(NULL != data);

    return container_at((container_t*)stack, data, container_size((container_t*)stack) - 1);
}

size_t stack_size(const stack_t* stack)
{
    assert(NULL != stack);

    return container_size((container_t*)stack);
}

bool stack_empty(const stack_t* stack)
{
    assert(stack);
    size_t size = container_size((container_t*)stack);
	return (size == 0);
}
