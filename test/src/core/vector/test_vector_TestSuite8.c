/**
 * @file    test_vector_TestSuite7.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Vector 8-bit data. This list of tests
 *          checks that all linked list methods are correct executes i.e. works with
 *          data as expected.
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "interface/allocator_if.h"
#include "vector.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
#define DEFAULT_CAPACITY        10
#define DEFAULT_BIGGER_CAPACITY 15
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________
static vector_t *vector = NULL;
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
  TEST_MESSAGE("Vector Complex Tests For 8-bit Data");
}

/**
 * \brief Test case to verify creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[VECTOR_TEST]: create");
  TEST_ASSERT_NOT_NULL(vector);
}

/**
 * @brief Tests the push front and pop front methods without triggering a resize.
 *
 * This unit test verifies the correct behavior of the `push_front` and `pop_front` methods
 * of the vector when they operate within the vector's default capacity (i.e., without
 * needing to resize the vector).
 *
 * If the vector's `push_front` and `pop_front` methods work correctly, the output array
 * should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_1(void)
{
  uint8_t input[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[DEFAULT_CAPACITY] = {1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t output[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push front/pop front without resize");

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_CAPACITY);
}

/**
 * @brief Tests the push front and pop front methods, ensuring they handle resizing correctly.
 *
 * This unit test aims to validate the functionality of the `push_front` and `pop_front` methods
 * of the vector when the operations exceed the initial default capacity and trigger a resize.
 *
 * If the vector's `push_front` and `pop_front` methods, along with its resizing mechanism, function as expected,
 * the output array should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_2(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 93, 67, 66, 54, 77};
  uint8_t expected[DEFAULT_BIGGER_CAPACITY] = {77, 54, 66, 67, 93, 1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push front/pop front with resize");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}

/**
 * @brief Tests the push back and pop back methods without triggering a resize.
 *
 * This unit test verifies the correct behavior of the `push_back` and `pop_back` methods
 * of the vector when they operate within the vector's default capacity (i.e., without
 * needing to resize the vector).
 *
 * If the vector's `push_back` and `pop_back` methods work correctly, the output array
 * should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_3(void)
{
  uint8_t input[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[DEFAULT_CAPACITY] = {1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t output[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push back/pop back without resize");

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_CAPACITY);
}

/**
 * @brief Tests the push back and pop back methods, ensuring they handle resizing correctly.
 *
 * This unit test aims to validate the functionality of the `push_back` and `pop_back` methods
 * of the vector when the operations exceed the initial default capacity and trigger a resize.
 *
 * If the vector's `push_back` and `pop_back` methods, along with its resizing mechanism, function as expected,
 * the output array should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_4(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 93, 67, 66, 54, 77};
  uint8_t expected[DEFAULT_BIGGER_CAPACITY] = {77, 54, 66, 67, 93, 1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push back/pop back with resize");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}

/**
 * @brief Tests the push front and pop back methods without triggering a resize.
 *
 * This unit test verifies the correct behavior of the `push_front` and `pop_back` methods
 * of the vector when they operate within the vector's default capacity (i.e., without
 * needing to resize the vector).
 *
 * If the vector's `push_front` and `pop_back` methods work correctly, the output array
 * should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_5(void)
{
  uint8_t input[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push front/pop back without resize");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_CAPACITY);
}

/**
 * @brief Tests the push front and pop back methods, ensuring they handle resizing correctly.
 *
 * This unit test aims to validate the functionality of the `push_front` and `pop_back` methods
 * of the vector when the operations exceed the initial default capacity and trigger a resize.
 *
 * If the vector's `push_front` and `pop_back` methods, along with its resizing mechanism, function as expected,
 * the output array should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_6(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 100, 90, 90, 56, 1};
  uint8_t expected[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push front/pop back with resize");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(vector->push_front(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_back(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}

/**
 * @brief Tests the push back and pop front methods without triggering a resize.
 *
 * This unit test verifies the correct behavior of the `push_back` and `pop_front` methods
 * of the vector when they operate within the vector's default capacity (i.e., without
 * needing to resize the vector).
 *
 * If the vector's `push_back` and `pop_front` methods work correctly, the output array
 * should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_7(void)
{
  uint8_t input[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[DEFAULT_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push back/pop front without resize");

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_CAPACITY);
}

/**
 * @brief Tests the push back and pop front methods, ensuring they handle resizing correctly.
 *
 * This unit test aims to validate the functionality of the `push_back` and `pop_front` methods
 * of the vector when the operations exceed the initial default capacity and trigger a resize.
 *
 * If the vector's `push_back` and `pop_front` methods, along with its resizing mechanism, function as expected,
 * the output array should be the reverse of the input array, matching the expected array.
 */
void test_TestCase_8(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 100, 90, 90, 56, 1};
  uint8_t expected[DEFAULT_BIGGER_CAPACITY] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: push back/pop front with resize");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->pop_front(vector, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}

/**
 * @brief Tests the functionality of the `at` method of the vector.
 *
 * This unit test is designed to validate the correct behavior of the vector's `at` method,
 * which retrieves an element at a specific index without removing it from the vector.
 *
 * The goal is to confirm that the `at` method can correctly fetch elements by their indices,
 * and that these elements remain in the vector after being accessed.
 */
void test_TestCase_9(void)
{
  uint8_t input[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[VECTOR_TEST]: at");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(vector->at(vector, &output[i], i));
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief Tests the `insert` method's functionality when inserting elements into an initially empty vector without
 * triggering a resize.
 *
 * This unit test aims to validate the correct behavior of the vector's `insert` method,
 * which places an element at a specified index in the vector, pushing the subsequent elements one position further.
 *
 * The key aspect being tested is that the vector should accurately insert elements without the need to resize
 * (since the total number of elements being inserted equals the vector's default capacity).
 */
void test_TestCase_10(void)
{
  uint8_t input[DEFAULT_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99};
  uint8_t expected[DEFAULT_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99};
  uint8_t output[DEFAULT_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: insert into empty without resize");

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
  }

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++)
  {
    vector->at(vector, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_CAPACITY);
}

/**
 * @brief Tests the `insert` method's capability to handle dynamic resizing when the vector exceeds its initial
 * capacity.
 *
 * This unit test is designed to validate the vector's ability to automatically resize when elements are inserted
 * beyond its initial capacity using the `insert` method.
 *
 * The critical aspect being tested is the vector's ability to maintain the integrity of its contents while resizing.
 */
void test_TestCase_11(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: insert with resize");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    vector->at(vector, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, DEFAULT_BIGGER_CAPACITY);
}

/**
 * @brief Tests the `insert` method's ability to insert elements at specific positions within the vector.
 *
 * This unit test is designed to validate the `insert` method's functionality by checking if it can correctly
 * insert given elements at specified indices within the vector.
 *
 * The critical aspect being tested is the `insert` method's capability to insert elements at the correct positions
 * without disrupting the order of the existing elements in the vector.
 */
void test_TestCase_12(void)
{
  uint8_t input[] = {1, 56, 90, 90, 100, 77, 54, 66, 67, 93};
  uint8_t expected[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[VECTOR_TEST]: insert method");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    vector->push_front(vector, &input[i]);
  }

  uint8_t values[] = {111, 33, 55, 77, 99};
  TEST_ASSERT_TRUE(vector->insert(vector, &values[0], 1));
  TEST_ASSERT_TRUE(vector->insert(vector, &values[1], 3));
  TEST_ASSERT_TRUE(vector->insert(vector, &values[2], 5));
  TEST_ASSERT_TRUE(vector->insert(vector, &values[3], 7));
  TEST_ASSERT_TRUE(vector->insert(vector, &values[4], 9));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    vector->at(vector, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief Tests the `extract` method's ability to remove and retrieve elements from specific positions within the
 * vector.
 *
 * This unit test is designed to validate the `extract` method's functionality by checking if it can correctly
 * remove elements from specified indices within the vector and return the removed values.
 *
 * The critical aspect being tested is the `extract` method's capability to remove and return elements from the correct
 * positions without disrupting the order of the other elements in the vector.
 */
void test_TestCase_13(void)
{
  uint8_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};
  uint8_t values[] = {111, 33, 55, 77, 99};
  uint8_t extracted[sizeof(values) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[VECTOR_TEST]: extract");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    vector->insert(vector, &input[i], i);
  }

  TEST_ASSERT_TRUE(vector->extract(vector, &extracted[0], 1));
  TEST_ASSERT_TRUE(vector->extract(vector, &extracted[1], 2));
  TEST_ASSERT_TRUE(vector->extract(vector, &extracted[2], 3));
  TEST_ASSERT_TRUE(vector->extract(vector, &extracted[3], 4));
  TEST_ASSERT_TRUE(vector->extract(vector, &extracted[4], 5));

  TEST_ASSERT_EQUAL_UINT8_ARRAY(values, extracted, sizeof(values) / sizeof(uint8_t));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    vector->at(vector, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief Tests the functionality of the `replace` method by verifying its ability to substitute elements at specific
 * positions within the vector.
 *
 * This unit test aims to validate the correct operation of the `replace` method. The test checks whether the method can
 * accurately replace elements at specified indices with new values, while ensuring that the remaining elements in the
 * vector are unaffected.
 *
 * The core functionality being tested is the `replace` method's ability to correctly substitute elements at the desired
 * positions without disturbing the order or content of the other elements in the vector.
 */
void test_TestCase_14(void)
{
  uint8_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {111, 111, 33, 33, 55, 55, 77, 77, 99, 99, 100, 90, 90, 56, 1};
  uint8_t values[] = {111, 33, 55, 77, 99};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[VECTOR_TEST]: replace");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    vector->insert(vector, &input[i], i);
  }

  TEST_ASSERT_TRUE(vector->replace(vector, &values[0], 0));
  TEST_ASSERT_TRUE(vector->replace(vector, &values[1], 2));
  TEST_ASSERT_TRUE(vector->replace(vector, &values[2], 4));
  TEST_ASSERT_TRUE(vector->replace(vector, &values[3], 6));
  TEST_ASSERT_TRUE(vector->replace(vector, &values[4], 8));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    vector->at(vector, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief Tests the functionality of the `erase` method by verifying its capability to correctly remove elements at
 * specific positions within the vector.
 *
 * This unit test is designed to validate the correct operation of the `erase` method. The test examines whether the
 * method can accurately remove elements at specified indices without affecting the integrity of the remaining items in
 * the vector.
 *
 * The central functionality being validated is the `erase` method's aptitude to remove elements from the desired
 * positions while maintaining the order and content of the vector's other elements.
 */
void test_TestCase_15(void)
{
  uint8_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 67, 66, 54, 77, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[VECTOR_TEST]: erase");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    vector->insert(vector, &input[i], i);
  }

  TEST_ASSERT_TRUE(vector->erase(vector, 1));
  TEST_ASSERT_TRUE(vector->erase(vector, 2));
  TEST_ASSERT_TRUE(vector->erase(vector, 3));
  TEST_ASSERT_TRUE(vector->erase(vector, 4));
  TEST_ASSERT_TRUE(vector->erase(vector, 5));

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    vector->at(vector, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief Tests the functionality of the `size` method by asserting its accuracy during sequential insertions (via
 * push_front) and deletions (via pop_front).
 *
 * This unit test is designed to validate the accurate reporting of the vector's size using the `size` method. The
 * validation process takes into account two primary operations:
 * 1. Insertion of elements to the front.
 * 2. Deletion of elements from the front.
 *
 * The primary goal of this test is to ensure that the `size` method consistently and accurately reports the vector's
 * current size throughout a series of insertions and deletions.
 */
void test_TestCase_16(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: size #1");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    vector->push_front(vector, &input[i]);
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(DEFAULT_BIGGER_CAPACITY - i, size);
    vector->pop_front(vector, &output[i]);
  }
}

/**
 * @brief Tests the accuracy of the `size` method during sequential operations of adding and removing elements.
 *
 * The primary objective of this test is to validate the proper functioning of the `size` method in two scenarios:
 * 1. When elements are sequentially added to the vector's end using the `push_back` method.
 * 2. When elements are sequentially removed from the vector's end using the `pop_back` method.
 *
 * During each operation, the test checks if the reported size of the vector matches the expected value. After adding
 * all the elements, the vector's size should increment with each insertion and decrement with each deletion, ensuring
 * that the `size` method provides accurate information at all times.
 */
void test_TestCase_17(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: size #2");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    vector->push_back(vector, &input[i]);
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(DEFAULT_BIGGER_CAPACITY - i, size);
    vector->pop_back(vector, &output[i]);
  }
}

/**
 * @brief Tests the accuracy of the `size` method during mixed operations of adding elements to the front and removing
 * from the back.
 *
 * This test is primarily designed to validate the correct behavior of the `size` method in two mixed scenarios:
 * 1. When elements are sequentially added to the vector's front using the `push_front` method.
 * 2. When elements are sequentially removed from the vector's back using the `pop_back` method.
 *
 * For each operation (addition or removal), the test assesses if the reported size of the vector corresponds with the
 * expected value. As elements are added to the front, the vector's size should consistently increase, and as elements
 * are removed from the back, it should consistently decrease. This ensures that the `size` method accurately reflects
 * the current number of elements in the vector during these mixed operations.
 */
void test_TestCase_18(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: size #3");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    vector->push_front(vector, &input[i]);
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(DEFAULT_BIGGER_CAPACITY - i, size);
    vector->pop_back(vector, &output[i]);
  }
}

/**
 * @brief Tests the accuracy of the `size` method during mixed operations of adding elements to the back and removing
 * from the front.
 *
 * This test aims to validate the correct behavior of the `size` method under two mixed scenarios:
 * 1. When elements are sequentially added to the vector's back using the `push_back` method.
 * 2. When elements are sequentially removed from the vector's front using the `pop_front` method.
 *
 * For each operation (addition or removal), the test checks if the reported size of the vector aligns with the expected
 * value. As elements are added to the back, the vector's size should progressively increase. Conversely, as elements
 * are removed from the front, the size should gradually decrease. This test confirms that the `size` method
 * consistently and accurately represents the current number of elements in the vector, even during these mixed
 * operations.
 */
void test_TestCase_19(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: size #4");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    vector->push_back(vector, &input[i]);
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(DEFAULT_BIGGER_CAPACITY - i, size);
    vector->pop_front(vector, &output[i]);
  }
}

/**
 * @brief Tests the accuracy of the `size` method during a combination of adding elements and accessing them without
 * modifying the vector's size.
 *
 * This test is designed to evaluate the behavior of the `size` method in the following sequence:
 * 1. Elements are sequentially added to the vector's back using the `push_back` method. After each addition, the test
 * verifies if the vector's reported size matches the expected count of elements.
 * 2. Once the vector is populated, elements are accessed using the `at` method. Despite accessing the elements, the
 * size of the vector should remain constant, as the `at` method does not modify the number of elements in the vector.
 *
 * The primary goal of this test is to confirm that the `size` method correctly represents the number of elements in the
 * vector when elements are added and subsequently accessed. It also ensures that merely accessing elements using the
 * `at` method doesn't inadvertently alter the size.
 */
void test_TestCase_20(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[DEFAULT_BIGGER_CAPACITY] = {};

  TEST_MESSAGE("[VECTOR_TEST]: size #5");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    vector->push_back(vector, &input[i]);
  }

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(DEFAULT_BIGGER_CAPACITY, size);
    vector->at(vector, &output[i], i);
  }
}

/**
 * @brief Tests the accuracy of the `size` method during sequential insertion of elements.
 *
 * The objective of this test is to ensure that the vector correctly updates its size as new elements are inserted. This
 * is achieved by performing the following sequence of operations:
 * 1. The test initializes an array of predefined values.
 * 2. Elements from this array are sequentially inserted into the vector at specific positions using the `insert`
 * method.
 * 3. After each insertion, the test checks if the vector's reported size is consistent with the number of inserted
 * elements.
 *
 * The test primarily focuses on validating the behavior of the `size` method when elements are added via the `insert`
 * method. It ensures that each insertion accurately increments the size by one and that the `size` method consistently
 * reflects the actual number of elements in the vector.
 */
void test_TestCase_21(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[VECTOR_TEST]: size #6");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(i, size);
    vector->insert(vector, &input[i], i);
  }
}

/**
 * @brief Tests the accuracy of the `size` method during sequential erasure of elements from the beginning of the
 * vector.
 *
 * This test ensures that the vector accurately updates its size as elements are sequentially removed from the beginning
 * of the vector. The sequence of operations is as follows:
 * 1. The test initializes an array with predefined values.
 * 2. Elements from this array are sequentially inserted into the vector using the `insert` method.
 * 3. After the vector is populated, elements are sequentially removed from the beginning of the vector using the
 * `erase` method.
 * 4. After each erasure, the test checks if the vector's reported size correctly reflects the number of remaining
 * elements.
 *
 * The primary goal of this test is to validate the behavior of the `size` method when elements are removed via the
 * `erase` method. It ensures that each removal accurately decrements the size by one and that the `size` method
 * consistently indicates the actual number of elements left in the vector.
 */
void test_TestCase_22(void)
{
  uint8_t input[DEFAULT_BIGGER_CAPACITY] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};

  TEST_MESSAGE("[VECTOR_TEST]: size #7");

  for (size_t i = 0; i < DEFAULT_BIGGER_CAPACITY; i++)
  {
    vector->insert(vector, &input[i], i);
  }

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(sizeof(input) / sizeof(uint8_t) - i, size);
    vector->erase(vector, 0);
  }
}

/**
 * @brief Tests the accuracy of the `size` method during sequential extraction of elements from the beginning of the
 * vector.
 *
 * This test ensures that the vector's size is correctly updated and reported as elements are sequentially extracted
 * from the beginning of the vector.
 *
 * The main objective of this test is to verify the behavior of the `size` method when elements are removed through the
 * `extract` method. It ensures that the vector's size is decremented appropriately with each extraction and that the
 * `size` method reliably indicates the actual number of elements in the vector.
 */
void test_TestCase_23(void)
{
  uint8_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output = 0;

  TEST_MESSAGE("[VECTOR_TEST]: size #8");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    vector->insert(vector, &input[i], i);
  }

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    size_t size = vector->size(vector);
    TEST_ASSERT_EQUAL_UINT8(sizeof(input) / sizeof(uint8_t) - i, size);
    vector->extract(vector, &output, 0);
  }
}

/**
 * @brief Tests the functionality of the `clear` method for the vector.
 *
 * By the end of this test, one can be confident in the vector's ability to correctly and fully clear its contents
 * without any residual data or side effects, and its readiness to be re-utilized post-clearance.
 */
void test_TestCase_24(void)
{
  uint8_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[VECTOR_TEST]: clear");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    vector->insert(vector, &input[i], i);
  }

  size_t size = vector->size(vector);
  TEST_ASSERT_EQUAL_UINT8(sizeof(expected) / sizeof(uint8_t), size);
  TEST_ASSERT_TRUE(vector->clear(vector));
  size = vector->size(vector);
  TEST_ASSERT_EQUAL_UINT8(0, size);

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(vector->insert(vector, &input[i], i));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    vector->at(vector, &output[i], i);
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}

/**
 * @brief Tests the functionality of the `peek` method by verifying its ability to access elements at specific
 * positions within the vector without removing them.
 *
 * This unit test is designed to validate the proper functioning of the `peek` method. The test ensures that the method
 * can accurately access and return pointers to elements at specified indices within the vector, without altering or
 * removing those elements. Additionally, the test ensures that accessing these elements doesn't affect the integrity
 * of the vector's content.
 *
 * The core functionality being tested is the `peek` method's ability to correctly provide pointers to elements at the
 * desired positions, allowing for indirect read access to the vector's content. It also validates that the structure
 * of the vector remains consistent after these operations, ensuring that `peek` is a non-destructive method.
 */
void test_TestCase_25(void)
{
  uint8_t input[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t expected[] = {93, 111, 67, 33, 66, 55, 54, 77, 77, 99, 100, 90, 90, 56, 1};
  uint8_t output[sizeof(expected) / sizeof(uint8_t)] = {};

  TEST_MESSAGE("[VECTOR_TEST]: peek");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint8_t); i++)
  {
    TEST_ASSERT_TRUE(vector->push_back(vector, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint8_t); i++)
  {
    uint8_t *out = vector->peek(vector, i);
    TEST_ASSERT_TRUE(out);
    output[i] = *out;
  }

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, sizeof(expected) / sizeof(uint8_t));
}
