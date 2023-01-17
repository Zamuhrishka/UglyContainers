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
struct test_ll_simple_struct
{
    uint32_t a;
    uint16_t b;
    uint8_t c;
};

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static linked_list_t* ll = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
    // container_init(malloc, free);
    ll = linked_list_create(sizeof(struct test_ll_simple_struct));
}

void tearDown(void)
{
    linked_list_delete(&ll);
}

void test_create(void)
{
    TEST_ASSERT_NOT_NULL(ll);
}

void test_push_front(void)
{
    struct test_ll_simple_struct actual = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    TEST_ASSERT_TRUE(ll->push_front(ll, &actual));
}

void test_pop_front(void)
{
    struct test_ll_simple_struct actual = {0};
    struct test_ll_simple_struct expected = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    ll->push_front(ll, &expected);

    TEST_ASSERT_TRUE(ll->pop_front(ll, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected.a, actual.a);
    TEST_ASSERT_EQUAL_UINT16(expected.b, actual.b);
    TEST_ASSERT_EQUAL_UINT8(expected.c, actual.c);
}

void test_push_back(void)
{
    struct test_ll_simple_struct actual = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    TEST_ASSERT_TRUE(ll->push_back(ll, &actual));
}

void test_pop_back(void)
{
    struct test_ll_simple_struct actual = {0};
    struct test_ll_simple_struct expected = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    ll->push_back(ll, &expected);

    TEST_ASSERT_TRUE(ll->pop_back(ll, &actual));
    TEST_ASSERT_EQUAL_UINT32(expected.a, actual.a);
    TEST_ASSERT_EQUAL_UINT16(expected.b, actual.b);
    TEST_ASSERT_EQUAL_UINT8(expected.c, actual.c);
}

void test_insert(void)
{
    struct test_ll_simple_struct actual = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    TEST_ASSERT_TRUE(ll->insert(ll, &actual, 0));
    TEST_ASSERT_TRUE(ll->insert(ll, &actual, 0));
}

void test_at(void)
{
    struct test_ll_simple_struct actual = {0};
    struct test_ll_simple_struct expected = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    ll->insert(ll, &expected, 0);

    TEST_ASSERT_TRUE(ll->at(ll, &actual, 0));
    TEST_ASSERT_EQUAL_UINT32(expected.a, actual.a);
    TEST_ASSERT_EQUAL_UINT16(expected.b, actual.b);
    TEST_ASSERT_EQUAL_UINT8(expected.c, actual.c);
}

void test_erase(void)
{
    struct test_ll_simple_struct actual = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    ll->insert(ll, &actual, 0);

    TEST_ASSERT_TRUE(ll->erase(ll, 0));
}

void test_size_empty(void)
{
    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(0, size);
}

void test_size(void)
{
    struct test_ll_simple_struct data = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    ll->push_front(ll, &data);

    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}