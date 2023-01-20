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
    vector = vector_create(sizeof(uint8_t));
}

void tearDown(void)
{
    vector_delete(&vector);
}

void test_init(void)
{
    TEST_MESSAGE("Vector Simple Tests For 8-bit Data");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("[VECTOR_TEST]: create");
    TEST_ASSERT_NOT_NULL(vector);
}

void test_TestCase_1(void)
{
    uint8_t input[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};

    TEST_MESSAGE("[VECTOR_TEST]: push front without resize");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }
}

void test_TestCase_2(void)
{
    int8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 93, 67, 66, 54, 77};

    TEST_MESSAGE("[VECTOR_TEST]: push front with resize");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }
}

void test_TestCase_3(void)
{
    uint8_t input = 0x55;

    TEST_MESSAGE("[VECTOR_TEST]: pop front");

    vector->push_front(vector, &input);

    TEST_ASSERT_TRUE(vector->pop_front(vector, &input));
}

void test_TestCase_4(void)
{
    uint8_t input[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};

    TEST_MESSAGE("[VECTOR_TEST]: push back without resize");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }
}

void test_TestCase_5(void)
{
    int8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 93, 67, 66, 54, 77};

    TEST_MESSAGE("[VECTOR_TEST]: push back with resize");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }
}

void test_TestCase_6(void)
{
    uint8_t input = 0x55;

    TEST_MESSAGE("[VECTOR_TEST]: pop back");

    vector->push_front(vector, &input);

    TEST_ASSERT_TRUE(vector->pop_back(vector, &input));
}


void test_TestCase_7(void)
{
    uint8_t input[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};

    TEST_MESSAGE("[VECTOR_TEST]: insert without resize");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
    }
}

void test_TestCase_8(void)
{
    int8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 93, 67, 66, 54, 77};

    TEST_MESSAGE("[VECTOR_TEST]: insert with resize");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
    }
}

void test_TestCase_9(void)
{
    uint8_t input = 0x55;
    uint8_t output = 0;

    TEST_MESSAGE("[VECTOR_TEST]: at");

    vector->insert(vector, &input, 0);

    TEST_ASSERT_TRUE(vector->at(vector, &output, 0));
}

void test_TestCase_10(void)
{
    uint8_t input = 0x55;

    TEST_MESSAGE("[VECTOR_TEST]: erase without resize");

    vector->insert(vector, &input, 0);

    TEST_ASSERT_TRUE(vector->erase(vector, 0));
}

void test_TestCase_11(void)
{
    TEST_MESSAGE("[VECTOR_TEST]: erase with resize");
    TEST_IGNORE_MESSAGE("Resize for erase haven`t implemented yet");
}

void test_TestCase_12(void)
{
    uint8_t input = 0x55;

    TEST_MESSAGE("[VECTOR_TEST]: size");

    vector->push_front(vector, &input);

    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(1, size);
}

void test_TestCase_13(void)
{
    uint8_t input = 0x55;
    uint8_t output = 0;

    TEST_MESSAGE("[VECTOR_TEST]: extract");

    vector->insert(vector, &input, 0);

    TEST_ASSERT_TRUE(vector->extract(vector, &output, 0));
    TEST_ASSERT_EQUAL_UINT8(output, input);
}

void test_TestCase_14(void)
{
    uint8_t input = 0x55;

    TEST_MESSAGE("[VECTOR_TEST]: clear");

    vector->insert(vector, &input, 0);

    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(1, size);
    TEST_ASSERT_TRUE(vector->clear(vector));
    size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(0, size);
}