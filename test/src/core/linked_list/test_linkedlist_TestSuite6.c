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
#include "linked_list.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static linked_list_t* ll = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    ll = linked_list_create(sizeof(uint32_t));
}

void tearDown(void)
{
    linked_list_delete(&ll);
}

void test_init(void)
{
    TEST_MESSAGE("Linked List Complex Tests For 32-bit Data");
}

void test_TestCase_0(void)
{
    TEST_MESSAGE("[LL_TEST]: Create");
    TEST_ASSERT_NOT_NULL(ll);
}

void test_TestCase_1(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: push front/pop front");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
    }

    for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->pop_front(ll, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_2(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: push back/pop back");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
    }

    for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->pop_back(ll, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_3(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: push front/pop back");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->pop_back(ll, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_4(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: push back/pop front");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->pop_front(ll, &output[i]));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}


void test_TestCase_5(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: at");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->push_back(ll, &input[i]));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->at(ll, &output[i], i));
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_6(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: insert #1");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->insert(ll, &input[i], i));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        ll->at(ll, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_7(void)
{
    uint32_t input[] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: insert #2");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->push_front(ll, &input[i]));
    }

    uint32_t values[] = {11111, 33333, 55555, 77777, 99999};  
    TEST_ASSERT_TRUE(ll->insert(ll, &values[0], 1));
    TEST_ASSERT_TRUE(ll->insert(ll, &values[1], 3));
    TEST_ASSERT_TRUE(ll->insert(ll, &values[2], 5));
    TEST_ASSERT_TRUE(ll->insert(ll, &values[3], 7));
    TEST_ASSERT_TRUE(ll->insert(ll, &values[4], 9));

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        ll->at(ll, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_8(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};
    uint32_t values[] = {11111, 33333, 55555, 77777, 99999}; 
    uint32_t extracted[sizeof(values)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: extract");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        ll->insert(ll, &input[i], i);
    }

    TEST_ASSERT_TRUE(ll->extract(ll, &extracted[0], 1));
    TEST_ASSERT_TRUE(ll->extract(ll, &extracted[1], 2));
    TEST_ASSERT_TRUE(ll->extract(ll, &extracted[2], 3));
    TEST_ASSERT_TRUE(ll->extract(ll, &extracted[3], 4));
    TEST_ASSERT_TRUE(ll->extract(ll, &extracted[4], 5));

    TEST_ASSERT_EQUAL_UINT32_ARRAY(values, extracted, sizeof(values)/sizeof(uint32_t));

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        ll->at(ll, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_9(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: erase");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        ll->insert(ll, &input[i], i);
    }

    TEST_ASSERT_TRUE(ll->erase(ll, 1));
    TEST_ASSERT_TRUE(ll->erase(ll, 2));
    TEST_ASSERT_TRUE(ll->erase(ll, 3));
    TEST_ASSERT_TRUE(ll->erase(ll, 4));
    TEST_ASSERT_TRUE(ll->erase(ll, 5));

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        ll->at(ll, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}

void test_TestCase_10(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: size #1");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        ll->push_front(ll, &input[i]);        
    }

    for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(sizeof(output)/sizeof(uint32_t) - i, size);
        ll->pop_front(ll, &output[i]);        
    }
}

void test_TestCase_11(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: size #2");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        ll->push_back(ll, &input[i]);        
    }

    for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(sizeof(output)/sizeof(uint32_t) - i, size);
        ll->pop_back(ll, &output[i]);        
    }
}

void test_TestCase_12(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: size #3");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        ll->push_front(ll, &input[i]);        
    }

    for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(sizeof(output)/sizeof(uint32_t) - i, size);
        ll->pop_back(ll, &output[i]);        
    }
}

void test_TestCase_13(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: size #4");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        ll->push_back(ll, &input[i]);        
    }

    for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(sizeof(output)/sizeof(uint32_t) - i, size);
        ll->pop_front(ll, &output[i]);        
    }
}

void test_TestCase_14(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: size #5");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        ll->push_back(ll, &input[i]);        
    }

    for (size_t i = 0; i < sizeof(output)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(sizeof(output)/sizeof(uint32_t), size);
        ll->at(ll, &output[i], i);        
    }
}

void test_TestCase_15(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};

    TEST_MESSAGE("[LL_TEST]: size #6");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        ll->insert(ll, &input[i], i);
    }
}

void test_TestCase_16(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};

    TEST_MESSAGE("[LL_TEST]: size #7");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        ll->insert(ll, &input[i], i);
    }

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(sizeof(input)/sizeof(uint32_t) - i, size);
        ll->erase(ll, 0);   
    }
}

void test_TestCase_17(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output = 0;

    TEST_MESSAGE("[LL_TEST]: size #8");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        ll->insert(ll, &input[i], i);
    }

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(sizeof(input)/sizeof(uint32_t) - i, size);
        ll->extract(ll, &output, 0);   
    }
}

void test_TestCase_18(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

    TEST_MESSAGE("[LL_TEST]: clear");

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        ll->insert(ll, &input[i], i);
    }

    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(sizeof(expected)/sizeof(uint32_t), size);
    TEST_ASSERT_TRUE(ll->clear(ll));
    size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(0, size);


    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        TEST_ASSERT_TRUE(ll->insert(ll, &input[i], i));
    }

    for (size_t i = 0; i < sizeof(expected)/sizeof(uint32_t); i++)
    {
        ll->at(ll, &output[i], i);
    }
    
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected)/sizeof(uint32_t));
}
