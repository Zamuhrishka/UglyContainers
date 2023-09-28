/**
 * @file test_Transformation_TestSuite0.c
 * @author Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-09-27
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "algorithms/transformation/transformation.h"
#include "interface/allocator_if.h"

// mock
#include "mock_container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
// typedef uint32_t container_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
container_t container = 0;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void test_TestCase_0(void)
{
  uint32_t output[2] = {};
  size_t arr_size = sizeof(output) / sizeof(uint32_t);

  // TEST_MESSAGE("[TRANSFORMATION]: Vector based container to array transformation test");

  // container_size_ExpectAndReturn(0);
  // container_size_IgnoreArg_container();

  container_size_IgnoreAndReturn(0);
  container_esize_IgnoreAndReturn(sizeof(uint32_t));
  container_at_IgnoreAndReturn(true);
  // container_at_ExpectAnyArgsAndReturn(true);

  bool status = to_array(&container, output, arr_size);
  TEST_ASSERT_TRUE(status);
}
