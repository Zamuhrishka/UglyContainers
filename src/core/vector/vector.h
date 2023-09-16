/**
 * @file vector.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "stdbool.h"
#include "stdint.h"

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Private_tag;
typedef struct Private_tag private_t;

typedef struct
{
  private_t* private;
  struct
  {
    bool (*resize)(void* this, size_t new_size);
    bool (*push_front)(void* this, const void* data);
    bool (*pop_front)(void* this, void* data);
    bool (*push_back)(void* this, const void* data);
    bool (*pop_back)(void* this, void* data);
    bool (*insert)(void* this, const void* data, size_t index);
    bool (*extract)(void* this, void* data, size_t index);
    bool (*replace)(void* this, const void* data, size_t index);
    bool (*at)(const void* this, void* data, size_t index);
    bool (*erase)(void* this, size_t index);
    void* (*peek)(void* this, size_t index);
    bool (*clear)(void* this);
    size_t (*size)(const void* this);
  };
} vector_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
vector_t* vector_create(size_t esize);
void vector_delete(vector_t** vector);
