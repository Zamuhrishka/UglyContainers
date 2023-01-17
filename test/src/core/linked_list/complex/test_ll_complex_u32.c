/**
 * @file test_ll.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdlib.h>
#include <string.h>

#include "allocator_if.h"
#include "container.h"
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
    container_init(malloc, free);
    ll = linked_list_create(sizeof(uint32_t));
}

void tearDown(void)
{
    linked_list_delete(&ll);
}

void test_create(void)
{
    TEST_ASSERT_NOT_NULL(ll);
}

void test_push_front_pop_front(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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

void test_push_back_pop_back(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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

void test_push_front_pop_back(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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

void test_push_back_pop_front(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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


void test_at(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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

void test_insert_in_exist(void)
{
    uint32_t input[] = {1, 562610, 907163, 90197, 10021, 771535, 54519, 66, 67793, 93274};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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

void test_insert_in_empty(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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

void test_erase(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};
    uint32_t expected[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(expected)/sizeof(uint32_t)] = {};

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

void test_front_size(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

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

void test_back_size(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

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

void test_front_back_size(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

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

void test_back_front_size(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

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

void test_at_size(void)
{
    uint32_t input[] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
    uint32_t output[sizeof(input)/sizeof(uint32_t)] = {};

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

void test_insert_size(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};

    for (size_t i = 0; i < sizeof(input)/sizeof(uint32_t); i++)
    {
        size_t size = ll->size(ll);
        TEST_ASSERT_EQUAL_UINT32(i, size);
        ll->insert(ll, &input[i], i);
    }
}

void test_erase_size(void)
{
    uint32_t input[] = {93274, 11111, 67793, 33333, 66, 55555, 54519, 77777, 771535, 99999, 10021, 90197, 907163, 562610, 1};

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