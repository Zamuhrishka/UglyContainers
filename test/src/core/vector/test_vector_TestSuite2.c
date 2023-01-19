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
    TEST_MESSAGE("Vector Complex Tests For 32-bit Data");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("Vector create test");
    TEST_ASSERT_NOT_NULL(vector);
}

void test_TestCase_1(void)
{
    uint32_t input[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[DEFAULT_CAPACITY] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[DEFAULT_CAPACITY] = {};

    TEST_MESSAGE("Vector push front/pop front without resize test");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_CAPACITY);
}

void test_TestCase_2(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 93274, 67793, 66, 54519, 771535};
    uint32_t expected[DEFAULT_BIGGER_CAPACITY] = {771535, 54519, 66, 67793, 93274, 1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Vector push front/pop front with resize test");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}


void test_TestCase_3(void)
{
    uint32_t input[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[DEFAULT_CAPACITY] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[DEFAULT_CAPACITY] = {};

    TEST_MESSAGE("Vector push back/pop back without resize test");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_CAPACITY);
}


void test_TestCase_4(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 93274, 67793, 66, 54519, 771535};
    uint32_t expected[DEFAULT_BIGGER_CAPACITY] = {771535, 54519, 66, 67793, 93274, 1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Vector push back/pop back with resize test");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}


void test_TestCase_5(void)
{
    uint32_t input[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_CAPACITY] = {};

    TEST_MESSAGE("Vector push front/pop back without resize test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_CAPACITY);
}

void test_TestCase_6(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Vector push front/pop back with resize test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}

void test_TestCase_7(void)
{
    uint32_t input[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[DEFAULT_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_CAPACITY] = {};

    TEST_MESSAGE("Vector push back/pop front without resize test");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_CAPACITY);
}

void test_TestCase_8(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[DEFAULT_BIGGER_CAPACITY] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Vector push back/pop front with resize test");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}

void test_TestCase_9(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("Vector at test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(vector->at(vector, &output[i], i));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_10(void)
{
    uint32_t input[DEFAULT_CAPACITY] =    {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999};
    uint32_t expected[DEFAULT_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999};
    uint32_t output[DEFAULT_CAPACITY] = {};

    TEST_MESSAGE("Vector insert into empty without resize test");

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
    }

    for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
    {
        vector->at(vector, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_CAPACITY);
}

void test_TestCase_11(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Vector insert into empty with resize test");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        vector->at(vector, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}


void test_TestCase_12(void)
{
    // TEST_IGNORE_MESSAGE("Strange behavior of test. Have to figure ou root cause!");

    uint32_t input[] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("Vector insert into exist test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        vector->push_front(vector, &input[i]);
    }

    uint32_t values[] = {11111, 33333, 55555, 77777, 99999};  
    TEST_ASSERT_TRUE(vector->insert(vector, &values[0], 1));
    TEST_ASSERT_TRUE(vector->insert(vector, &values[1], 3));
    TEST_ASSERT_TRUE(vector->insert(vector, &values[2], 5));
    TEST_ASSERT_TRUE(vector->insert(vector, &values[3], 7));
    TEST_ASSERT_TRUE(vector->insert(vector, &values[4], 9));

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        vector->at(vector, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_13(void)
{
    // TEST_IGNORE_MESSAGE("Test fault. Have to figure ou root cause!");

    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("Vector erase test");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        vector->insert(vector, &input[i], i);
    }

    TEST_ASSERT_TRUE(vector->erase(vector, 1));
    TEST_ASSERT_TRUE(vector->erase(vector, 2));
    TEST_ASSERT_TRUE(vector->erase(vector, 3));
    TEST_ASSERT_TRUE(vector->erase(vector, 4));
    TEST_ASSERT_TRUE(vector->erase(vector, 5));

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        vector->at(vector, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_14(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Test for checking of size() with push/pop front functions");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        vector->push_front(vector, &input[i]);        
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(DEFAULT_BIGGER_CAPACITY - i, size);
        vector->pop_front(vector, &output[i]);        
    }
}

void test_TestCase_15(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Test for checking of size() with push/pop back functions");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        vector->push_back(vector, &input[i]);        
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(DEFAULT_BIGGER_CAPACITY - i, size);
        vector->pop_back(vector, &output[i]);        
    }
}

void test_TestCase_16(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Test for checking of size() with push front/pop back functions");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        vector->push_front(vector, &input[i]);        
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(DEFAULT_BIGGER_CAPACITY - i, size);
        vector->pop_back(vector, &output[i]);        
    }
}

void test_TestCase_17(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Test for checking of size() with push back/pop front functions");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        vector->push_back(vector, &input[i]);        
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(DEFAULT_BIGGER_CAPACITY - i, size);
        vector->pop_front(vector, &output[i]);        
    }
}

void test_TestCase_18(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[DEFAULT_BIGGER_CAPACITY] = {};

    TEST_MESSAGE("Test for checking of size() with at functions");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        vector->push_back(vector, &input[i]);        
    }

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(DEFAULT_BIGGER_CAPACITY, size);
        vector->at(vector, &output[i], i);        
    }
}

void test_TestCase_19(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};

    TEST_MESSAGE("Test for checking of size() with insert function");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        vector->insert(vector, &input[i], i);
    }
}

void test_TestCase_20(void)
{
    uint32_t input[DEFAULT_BIGGER_CAPACITY] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};

    TEST_MESSAGE("Test for checking of size() with erase function");

    for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
    {
        vector->insert(vector, &input[i], i);
    }

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = vector->size(vector);
        TEST_ASSERT_EQUAL_UINT32(sizeof(input)/sizeof(uint32_t) - i, size);
        vector->erase(vector, 0);   
    }
}

void test_TestCase_21(void)
{
    TEST_MESSAGE("Vector EXTRACT test");
    TEST_IGNORE_MESSAGE("Test not implemented!");
}

void test_TestCase_22(void)
{
    TEST_MESSAGE("Vector CLEAR test");
    TEST_IGNORE_MESSAGE("Test not implemented!");
}