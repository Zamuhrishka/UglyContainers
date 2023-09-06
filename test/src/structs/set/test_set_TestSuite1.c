/**
 * @file test_set_TestSuite1.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-02-05
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdint.h>
#include <stdbool.h>

#include "core/allocator_if.h"
#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "structs/set/set.h"
//_____ C O N F I G S  ________________________________________________________
#define SET_MAX_SIZE    32
//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static set_t* set = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
static bool cmp(void* value1, void* value2)
{
    uint32_t* v1 = (uint32_t*)value1;
    uint32_t* v2 = (uint32_t*)value2;

    return *v1 == *v2;
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    set = set_create(SET_MAX_SIZE, sizeof(uint32_t), cmp);
}

void tearDown(void)
{
    set_delete(set);
}

void test_init(void)
{
    TEST_MESSAGE("Simple Unit Tests for Set");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("[SET_TEST]: create");
    TEST_ASSERT_NOT_NULL(set);
}

//Тестирование добавления первого элемента в пустое множество.
void test_TestCase_1(void)
{
	uint32_t data = 0x55AA55AA;

    TEST_MESSAGE("[STACK_TEST]: add");
    TEST_ASSERT_TRUE(set_add(set, &data));
}

//Тестирование добавления дубликатов в множество.
void test_TestCase_2(void)
{
	uint32_t data = 0x55AA55AA;

    TEST_MESSAGE("[STACK_TEST]: add duplicates");
    TEST_ASSERT_TRUE(set_add(set, &data));
    TEST_ASSERT_FALSE(set_add(set, &data));
}

void test_TestCase_3(void)
{
	uint32_t data = 0x55AA55AA;
	uint32_t data1 = 0xAA55AA55;

    TEST_MESSAGE("[STACK_TEST]: contain");

    set_add(set, &data);

    TEST_ASSERT_TRUE(set_contain(set, &data));
    TEST_ASSERT_FALSE(set_contain(set, &data1));
}

void test_TestCase_4(void)
{
	uint32_t data = 0x55AA55AA;

    TEST_MESSAGE("[STACK_TEST]: remove");

    set_add(set, &data);

    TEST_ASSERT_TRUE(set_remove(set, &data));
    TEST_ASSERT_FALSE(set_contain(set, &data));
}