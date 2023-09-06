/**
 * @file test_set_TestSuite2.c
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
    TEST_MESSAGE("Edge Conditions Tests for Set");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("[SET_TEST]: create");
    TEST_ASSERT_NOT_NULL(set);
}

//Тестирование добавления максимально возможного числа элементов в множество.
void test_TestCase_1(void)
{
	uint32_t input[SET_MAX_SIZE] = {
        0x73c7f3d3, 0x4dc55b72, 0x7e5f067c, 0x2eefb0f5,
        0x9c93b62a, 0x0d5a17f7, 0xeb52de6b, 0x2df4e4d3,
        0x80e2c3d3, 0x3b0a37b3, 0x25a9ca9e, 0x2266ddbb,
        0x8237584f, 0xd7e0f425, 0x8e68cb2b, 0xdc40b336,
        0xebcf7562, 0x7739e0dd, 0xbd2f2496, 0xdce2d85e,
        0x0f99c3e9, 0x8ca0d0cd, 0xdcddf14f, 0x6c17ac6f,
        0x6f5837e3, 0x07be7b32, 0x0d867d05, 0x2c01da16,
        0xd543f986, 0x66ed0e8f, 0x1a38b776, 0x241450b9
    };

    TEST_MESSAGE("[SET_TEST]: Max elements adding");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(set_add(set, &input[i]));
    }

    TEST_ASSERT_FALSE(set_add(set, &input[0]));
}

//Тестирование удаления всех элементов из множества.
void test_TestCase_2(void)
{
	uint32_t input[SET_MAX_SIZE] = {
        0x73c7f3d3, 0x4dc55b72, 0x7e5f067c, 0x2eefb0f5,
        0x9c93b62a, 0x0d5a17f7, 0xeb52de6b, 0x2df4e4d3,
        0x80e2c3d3, 0x3b0a37b3, 0x25a9ca9e, 0x2266ddbb,
        0x8237584f, 0xd7e0f425, 0x8e68cb2b, 0xdc40b336,
        0xebcf7562, 0x7739e0dd, 0xbd2f2496, 0xdce2d85e,
        0x0f99c3e9, 0x8ca0d0cd, 0xdcddf14f, 0x6c17ac6f,
        0x6f5837e3, 0x07be7b32, 0x0d867d05, 0x2c01da16,
        0xd543f986, 0x66ed0e8f, 0x1a38b776, 0x241450b9
    };

    TEST_MESSAGE("[SET_TEST]: Remove all elements");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        set_add(set, &input[i]);
    }

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        TEST_ASSERT_TRUE(set_remove(set, &input[i]));
    }

    size_t size = set_size(set);

    TEST_ASSERT_EQUAL_UINT32(0, size);
}

void test_TestCase_3(void)
{
    uint32_t input = 0x55AA55AA;

    TEST_MESSAGE("[SET_TEST]: Remove from empty");

    TEST_ASSERT_FALSE(set_remove(set, &input));
}

//Тестирование добавления элементов с минимальными и максимальными значениями uint32_t.
void test_TestCase_4(void)
{
    uint32_t min_input_value = 0;
    uint32_t max_input_value = (uint32_t)(-1);

    TEST_MESSAGE("[SET_TEST]: Min/max input values");

    TEST_ASSERT_TRUE(set_add(set, &min_input_value));
    TEST_ASSERT_TRUE(set_contain(set, &min_input_value));

    TEST_ASSERT_TRUE(set_add(set, &max_input_value));
    TEST_ASSERT_TRUE(set_contain(set, &max_input_value));
}

void test_TestCase_5(void)
{
    uint32_t input = 0x55AA55AA;

    TEST_MESSAGE("[SET_TEST]: Contain empty");

    TEST_ASSERT_FALSE(set_contain(set, &input));
}

void test_TestCase_6(void)
{
    uint32_t input = 0x55AA55AA;

    TEST_MESSAGE("[SET_TEST]: size #1");

    size_t size = set_size(set);

    TEST_ASSERT_EQUAL_UINT32(0, size);
}

void test_TestCase_7(void)
{
	uint32_t input[SET_MAX_SIZE] = {
        0x73c7f3d3, 0x4dc55b72, 0x7e5f067c, 0x2eefb0f5,
        0x9c93b62a, 0x0d5a17f7, 0xeb52de6b, 0x2df4e4d3,
        0x80e2c3d3, 0x3b0a37b3, 0x25a9ca9e, 0x2266ddbb,
        0x8237584f, 0xd7e0f425, 0x8e68cb2b, 0xdc40b336,
        0xebcf7562, 0x7739e0dd, 0xbd2f2496, 0xdce2d85e,
        0x0f99c3e9, 0x8ca0d0cd, 0xdcddf14f, 0x6c17ac6f,
        0x6f5837e3, 0x07be7b32, 0x0d867d05, 0x2c01da16,
        0xd543f986, 0x66ed0e8f, 0x1a38b776, 0x241450b9
    };

    TEST_MESSAGE("[SET_TEST]: size #2");

    for (size_t i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        set_add(set, &input[i]);
    }

    size_t size = set_size(set);
    TEST_ASSERT_EQUAL_UINT32(SET_MAX_SIZE, size);
}