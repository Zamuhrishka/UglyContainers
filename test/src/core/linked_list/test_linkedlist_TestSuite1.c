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
    ll = linked_list_create(sizeof(uint8_t));
}

void tearDown(void)
{
    linked_list_delete(&ll);
}


void test_init(void)
{
    TEST_MESSAGE("Linked List Simple Tests For 8-bit Data");
}


void test_TestCase_0(void)
{
    TEST_MESSAGE("Linked List CREATE test");
    TEST_ASSERT_NOT_NULL(ll);
}

void test_TestCase_1(void)
{
    uint8_t actual = 0x55555555;
    TEST_MESSAGE("Linked List PUSH FRONT test");
    TEST_ASSERT_TRUE(ll->push_front(ll, &actual));
}

void test_TestCase_2(void)
{
    uint8_t actual = 0;
    uint8_t expected = 0x55555555;

    TEST_MESSAGE("Linked List POP FRONT test");

    ll->push_front(ll, &expected);

    TEST_ASSERT_TRUE(ll->pop_front(ll, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_TestCase_3(void)
{
    uint8_t actual = 0x55555555;
    TEST_MESSAGE("Linked List PUSH BACK test");
    TEST_ASSERT_TRUE(ll->push_back(ll, &actual));
}

void test_TestCase_4(void)
{
    uint8_t actual = 0;
    uint8_t expected = 0x55555555;

    TEST_MESSAGE("Linked List POP BACK test");

    ll->push_back(ll, &expected);

    TEST_ASSERT_TRUE(ll->pop_back(ll, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_TestCase_5(void)
{
    uint8_t actual = 0x55555555;
    TEST_MESSAGE("Linked List INSERT test");
    TEST_ASSERT_TRUE(ll->insert(ll, &actual, 0));
    TEST_ASSERT_TRUE(ll->insert(ll, &actual, 0));
}

void test_TestCase_6(void)
{
    uint8_t expected = 0x55555555;
    uint8_t actual = 0;

    TEST_MESSAGE("Linked List AT test");

    ll->insert(ll, &expected, 0);

    TEST_ASSERT_TRUE(ll->at(ll, &actual, 0));
    TEST_ASSERT_EQUAL_UINT32(expected, actual);
}

void test_TestCase_7(void)
{
    uint8_t actual = 0x55555555;

    TEST_MESSAGE("Linked List ERASE test");

    ll->insert(ll, &actual, 0);

    TEST_ASSERT_TRUE(ll->erase(ll, 0));
}

void test_TestCase_8(void)
{
    uint8_t data = 0x55555555;

    TEST_MESSAGE("Linked List SIZE test");

    ll->push_front(ll, &data);

    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}