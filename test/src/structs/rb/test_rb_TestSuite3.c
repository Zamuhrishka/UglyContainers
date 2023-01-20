/**
 * @file test_ll.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdint.h>
#include <stdbool.h>

#include "core/allocator_if.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "structs/rb/ring_buffer.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
#define RB_MAX_SIZE 32
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static ring_buffer_t* rb = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{

}

void tearDown(void)
{

}

void test_init(void)
{
    TEST_MESSAGE("RingBuffer Complex Tests");
    TEST_IGNORE_MESSAGE("This TestSuite haven`t implemented");
}