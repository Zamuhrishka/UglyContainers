//==============================================================================
// !!!!!!!!!!!!!!!!!!!!!!!!!!! IN DEVELOPMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//==============================================================================
#if 0
/**
 * @file iterator.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

  #pragma once

//_____ I N C L U D E S _______________________________________________________
  #include <stdbool.h>
  #include <stdint.h>

  #include "core/container.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
struct Iterator_tag;
typedef struct Iterator_tag iterator_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
iterator_t *iterator_create(const container_t *container);
void iterator_delete(iterator_t **iterator);
bool iterator_next(const iterator_t *iterator);
bool iterator_prev(const iterator_t *iterator);
bool iterator_start(const iterator_t *iterator);
bool iterator_end(const iterator_t *iterator);
// bool iterator_reset(const iterator_t *iterator);
bool iterator_get(const iterator_t *iterator, void *data);
bool iterator_set(iterator_t *iterator, const void *data);
#endif
