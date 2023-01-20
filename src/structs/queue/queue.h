/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"

#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
typedef container_t queue_t;
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
queue_t* queue_create(size_t esize);
void queue_delete(queue_t** queue);
bool queue_empty(const queue_t* queue);
bool queue_dequeue(queue_t* queue, void* data);
bool queue_enqueue(queue_t* queue, const void* data);
bool queue_peek(const queue_t* queue, void* data);
size_t queue_size(const queue_t* queue);
bool queue_clear(queue_t* queue);