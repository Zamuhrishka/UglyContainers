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
    ll = linked_list_create(sizeof(struct test_ll_simple_struct));
}

void tearDown(void)
{
    linked_list_delete(&ll);
}


void test_init(void)
{
    TEST_MESSAGE("Linked List Simple Tests For struct Data");
}


void test_TestCase_0(void)
{
    TEST_MESSAGE("Linked List CREATE test");
    TEST_ASSERT_NOT_NULL(ll);
}

void test_TestCase_1(void)
{
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    TEST_MESSAGE("Linked List PUSH FRONT test");
    TEST_ASSERT_TRUE(ll->push_front(ll, &input));
}

void test_TestCase_2(void)
{
    struct test_ll_simple_struct output = {};
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    TEST_MESSAGE("Linked List POP FRONT test");

    ll->push_front(ll, &input);

    TEST_ASSERT_TRUE(ll->pop_front(ll, &output));
    TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
    TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
    TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

void test_TestCase_3(void)
{
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    TEST_MESSAGE("Linked List PUSH BACK test");
    TEST_ASSERT_TRUE(ll->push_back(ll, &input));
}

void test_TestCase_4(void)
{
    struct test_ll_simple_struct output = {};
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    TEST_MESSAGE("Linked List POP BACK test");

    ll->push_back(ll, &input);

    TEST_ASSERT_TRUE(ll->pop_back(ll, &output));    
    TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
    TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
    TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

void test_TestCase_5(void)
{
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    TEST_MESSAGE("Linked List INSERT test");
    TEST_ASSERT_TRUE(ll->insert(ll, &input, 0));
    TEST_ASSERT_TRUE(ll->insert(ll, &input, 0));
}

void test_TestCase_6(void)
{
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};
    struct test_ll_simple_struct output = {};

    TEST_MESSAGE("Linked List AT test");

    ll->insert(ll, &input, 0);

    TEST_ASSERT_TRUE(ll->at(ll, &output, 0));
    TEST_ASSERT_EQUAL_UINT32(output.a, input.a);
    TEST_ASSERT_EQUAL_UINT16(output.b, input.b);
    TEST_ASSERT_EQUAL_UINT8(output.c, input.c);
}

void test_TestCase_7(void)
{
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    TEST_MESSAGE("Linked List ERASE test");

    ll->insert(ll, &input, 0);

    TEST_ASSERT_TRUE(ll->erase(ll, 0));
}

void test_TestCase_8(void)
{
    struct test_ll_simple_struct input = {.a = 0x55555555, .b = 0x5555, .c = 0x55};

    TEST_MESSAGE("Linked List SIZE test");

    ll->push_front(ll, &input);

    size_t size = ll->size(ll);
    TEST_ASSERT_EQUAL_UINT32(1, size);
}

void test_TestCase_9(void)
{
    TEST_MESSAGE("Linked List EXTRACT test");
    TEST_IGNORE_MESSAGE("Test not implemented!");
}