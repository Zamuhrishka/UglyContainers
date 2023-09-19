/**
 * @file    uc_assert.h
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date    2023-09-16
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <assert.h>
//_____ C O N F I G S  ________________________________________________________
#if defined(TEST)
  #include "CException.h"
  #undef assert
  #define assert(condition) \
    do                      \
    {                       \
      if (!(condition))     \
        Throw(0);           \
    } while (0)
#endif
//_____ D E F I N I T I O N S _________________________________________________
#define UC_ASSERT assert
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
