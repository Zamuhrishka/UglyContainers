//==============================================================================
// !!!!!!!!!!!!!!!!!!!!!!!!!!! IN DEVELOPMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//==============================================================================
#if 0
/**
 * @file msc.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

  #pragma once

//_____ I N C L U D E S _______________________________________________________
  #include <stdbool.h>
  #include <stdint.h>

  #include "core/container.h"
  #include "structs/ds.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
// typedef bool (*PFCMP_t)(void *data1, void *data2);
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
// bool uc_to_array(const container_t *container, void *arr, size_t arr_size);
// bool uc_from_array(container_t *container, void *arr, size_t size);

void to_string(const container_t *container, char *string);

bool unique(container_t *container);
bool fill(container_t *container, size_t start, size_t end, void *value);
container_t *reverse(container_t *container);
#endif
