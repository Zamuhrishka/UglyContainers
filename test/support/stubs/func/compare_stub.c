/**
 * @file compare_stub.c
 * @author Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-09-30
 */

//_____ I N C L U D E S _______________________________________________________
#include "compare_stub.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
bool compare_false(const void *value1, const void *value2, size_t esize)
{
  return false;
}

bool compare_true(const void *value1, const void *value2, size_t esize)
{
  return true;
}
