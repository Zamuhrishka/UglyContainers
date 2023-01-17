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
#include "vector.h"

//_____ C O N F I G S  ________________________________________________________
// #define CONTAINER_TYPE 2
//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static vector_t* vector = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    // container_init(malloc, free);
    vector = vector_create(sizeof(uint32_t));
}

void tearDown(void)
{
    vector_delete(&vector);
}

void test_create(void)
{
    TEST_ASSERT_NOT_NULL(vector);
}

void test_push_front(void)
{
    uint32_t actual = 0x55555555;
    TEST_ASSERT_TRUE(vector->push_front(vector, &actual));
}

void test_pop_front(void)
{
    uint32_t actual = 0;
    uint32_t expected = 0x55555555;

    vector->push_front(vector, &expected);

    TEST_ASSERT_TRUE(vector->pop_front(vector, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_push_back(void)
{
    uint32_t actual = 0x55555555;
    TEST_ASSERT_TRUE(vector->push_back(vector, &actual));
}

void test_pop_back(void)
{
    uint32_t actual = 0;
    uint32_t expected = 0x55555555;

    vector->push_back(vector, &expected);

    TEST_ASSERT_TRUE(vector->pop_back(vector, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_insert(void)
{
    uint32_t actual = 0x55555555;
    TEST_ASSERT_TRUE(vector->insert(vector, &actual, 0));
    TEST_ASSERT_TRUE(vector->insert(vector, &actual, 0));
}

void test_at(void)
{
    uint32_t expected = 0x55555555;
    uint32_t actual = 0;

    vector->insert(vector, &expected, 0);

    TEST_ASSERT_TRUE(vector->at(vector, &actual, 0));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_erase(void)
{
    uint32_t actual = 0x55555555;

    vector->insert(vector, &actual, 0);

    TEST_ASSERT_TRUE(vector->erase(vector, 0));
}

void test_size_empty(void)
{
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT32(0, size);
}

void test_size(void)
{
    uint32_t data = 0x55555555;
    vector->push_front(vector, &data);

    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}