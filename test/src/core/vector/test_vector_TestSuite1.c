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

#include "allocator_if.h"
#include "vector.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
#define DEFAULT_CAPACITY 10
#define DEFAULT_BIGGER_CAPACITY 15
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static vector_t* vector = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    vector = vector_create(sizeof(uint32_t));
}

void tearDown(void)
{
    vector_delete(&vector);
}

void test_init(void)
{
    TEST_MESSAGE("Vector Simple Tests For 32-bit Data");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("Vector create test");
    TEST_ASSERT_NOT_NULL(vector);
}

void test_TestCase_1(void)
{
    uint32_t input[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};

    TEST_MESSAGE("Vector push front without resize test");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }
}

void test_TestCase_2(void)
{
    int32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 93274, 67793, 66, 54519, 771535};

    TEST_MESSAGE("Vector push front with resize test");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }
}

void test_TestCase_3(void)
{
    uint32_t input = 0x55555555;

    TEST_MESSAGE("Vector pop front test");

    vector->push_front(vector, &input);

    TEST_ASSERT_TRUE(vector->pop_front(vector, &input));
}

void test_TestCase_4(void)
{
    uint32_t input[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};

    TEST_MESSAGE("Vector push back without resize test");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }
}

void test_TestCase_5(void)
{
    int32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 93274, 67793, 66, 54519, 771535};

    TEST_MESSAGE("Vector push back with resize test");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }
}


void test_TestCase_6(void)
{
    uint32_t input = 0x55555555;

    TEST_MESSAGE("Vector pop back test");

    vector->push_front(vector, &input);

    TEST_ASSERT_TRUE(vector->pop_back(vector, &input));
}


void test_TestCase_7(void)
{
    uint32_t input[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};

    TEST_MESSAGE("Vector insert without resize test");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
    }
}

void test_TestCase_8(void)
{
    int32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 93274, 67793, 66, 54519, 771535};

    TEST_MESSAGE("Vector insert with resize test");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
    }
}

void test_TestCase_9(void)
{
    uint32_t input = 0x55555555;
    uint32_t output = 0;

    TEST_MESSAGE("Vector at test");

    vector->insert(vector, &input, 0);

    TEST_ASSERT_TRUE(vector->at(vector, &output, 0));
}

void test_TestCase_10(void)
{
    uint32_t actual = 0x55555555;

    TEST_MESSAGE("Vector erase without resize test");

    vector->insert(vector, &actual, 0);

    TEST_ASSERT_TRUE(vector->erase(vector, 0));
}

void test_TestCase_11(void)
{
    uint32_t actual = 0x55555555;

    TEST_MESSAGE("Vector erase with resize test");
    TEST_IGNORE_MESSAGE("Not implemented");

    vector->insert(vector, &actual, 0);

    TEST_ASSERT_TRUE(vector->erase(vector, 0));
}

void test_TestCase_12(void)
{
    uint32_t data = 0x55555555;

    TEST_MESSAGE("Vector get size test");

    vector->push_front(vector, &data);

    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}