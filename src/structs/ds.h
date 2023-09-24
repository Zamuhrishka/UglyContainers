/**
 * @file    ds.h
 * @author  Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Interface structure which need to support all data structures to has
 *          unify interface for algorithm module.
 * @date    2023-09-24
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
typedef struct
{
  container_t *container; /**< Pointer to the universal container */
  void *private; /**< Pointer to the private structure which contain fields specific for current data structure */
} ds_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
