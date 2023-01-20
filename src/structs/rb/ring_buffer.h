/**
 * @file ring_buffer.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-18
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________
#include "status_codes.h"

#include <stdint.h>
#include <stdbool.h>
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct RingBuffer_tag;
typedef struct RingBuffer_tag ring_buffer_t;
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
ring_buffer_t* rb_create(size_t size, size_t esize);
void rb_delete(ring_buffer_t** rb);

bool rb_is_empty(const ring_buffer_t* rb);
bool rb_is_full(const ring_buffer_t* rb);
bool rb_add(ring_buffer_t* rb, const void* data);
bool rb_get(ring_buffer_t* rb, void* data);

bool rb_peek(const ring_buffer_t* rb, void* data);
size_t rb_size(const ring_buffer_t* rb);
bool rb_clear(ring_buffer_t* rb);
