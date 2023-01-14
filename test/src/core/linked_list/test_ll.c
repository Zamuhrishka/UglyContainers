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

void test_push_front_simple(void)
{
    uint32_t actual = 0x55555555;
    TEST_ASSERT_TRUE(ll->push_front(ll, &actual));
}

void test_pop_front_empty(void)
{
    uint32_t actual = 0;
    TEST_ASSERT_FALSE(ll->pop_front(ll, &actual));
}

void test_pop_front_simple(void)
{
    uint32_t actual = 0;
    uint32_t expected = 0x55555555;

    ll->push_front(ll, &expected);

    TEST_ASSERT_TRUE(ll->pop_front(ll, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_push_back_simple(void)
{
    uint32_t actual = 0x55555555;

    TEST_ASSERT_TRUE(ll->push_back(ll, &actual));
}

void test_pop_back_empty(void)
{
    uint32_t actual = 0;

    TEST_ASSERT_FALSE(ll->pop_back(ll, &actual));
}

void test_pop_back_simple(void)
{
    uint32_t actual = 0;
    uint32_t expected = 0x55555555;

    ll->push_back(ll, &expected);

    TEST_ASSERT_TRUE(ll->pop_back(ll, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_insert_simple(void)
{
    uint32_t actual = 0x55555555;

    TEST_ASSERT_TRUE(ll->insert(ll, &actual, 0));
}

void test_insert_overflow(void)
{
    uint32_t actual = 0x55555555;

    TEST_ASSERT_FALSE(ll->insert(ll, &actual, 2));
}

void test_at_empty(void)
{
    uint32_t actual = 0;

    TEST_ASSERT_FALSE(ll->at(ll, &actual, 0));
}

void test_at_simple(void)
{
    uint32_t expected = 0x55555555;
    uint32_t actual = 0;

    ll->insert(ll, &expected, 0);

    TEST_ASSERT_TRUE(ll->at(ll, &actual, 0));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_erase_empty(void)
{
    TEST_ASSERT_FALSE(ll->erase(ll, 0));
}

void test_erase_overflow(void)
{
    uint32_t actual = 0x55555555;

    ll->insert(ll, &actual, 0);

    TEST_ASSERT_FALSE(ll->erase(ll, 2));
}

void test_erase_normal(void)
{
    uint32_t actual = 0x55555555;

    ll->insert(ll, &actual, 0);

    TEST_ASSERT_TRUE(ll->erase(ll, 0));
}

void test_size_empty(void)
{
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(0, size);
}

void test_size_push_front(void)
{
    uint32_t data = 0x55555555;
    TEST_ASSERT_TRUE(ll->push_front(ll, &data));

    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}