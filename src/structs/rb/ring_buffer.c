/**
 * @file ring_buffer.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-18
 */

//_____ I N C L U D E S _______________________________________________________
#include "ring_buffer.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "allocator_if.h"
#include "core/container.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
/**
*  \brief
*/
struct RingBuffer_tag
{
    container_t* container;
    volatile size_t tail;
    volatile size_t head;
    volatile size_t max_size;
    volatile bool overflow;
} ;

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
ring_buffer_t* rb_create(size_t size, size_t esize)
{
    assert(0 != esize);
    assert(0 != size);

    if (!is_allocator_valid())
    {
        return NULL;
    }

    allocate_fn_t mem_allocate = get_allocator();
    free_fn_t mem_free = get_free();

    ring_buffer_t* rb = (ring_buffer_t*)mem_allocate(sizeof(ring_buffer_t));
    if (NULL == rb)
    {
        return NULL;
    }


    rb->container = container_create(esize, CONTAINER_VECTOR_BASED);
    if (NULL == rb->container)
    {
        return NULL;
    }

    rb->head = 0;
    rb->tail = 0;
    rb->max_size = size;

    return rb;
}

void rb_delete(ring_buffer_t** rb)
{
    assert(*rb);
    assert(rb);

    container_delete((container_t**)(*rb)->container);
}

bool rb_add(ring_buffer_t* rb, const void* data)
{
    assert(rb);

    if(rb_is_full(rb)) {
		return false;
	}

    if(!container_insert(rb->container, data, rb->head)) {
        return false;
    }

    rb->head = (rb->head == container_size((container_t*)rb->container)) ? 0 : (rb->head + 1);
    // rb->head = (rb->head +1) % rb->max_size;

	return true;
}

bool rb_get(ring_buffer_t* rb, void* data)
{
    assert(rb);

    if(!container_extract((container_t*)rb->container, data, rb->tail)) {
        return false;
    }

    rb->tail = (rb->tail == container_size((container_t*)rb->container)) ? 0 : (rb->tail + 1);
    // rb->tail = (rb->tail +1) % rb->max_size;
}

bool rb_peek(const ring_buffer_t* rb, void* data)
{
    assert(rb);

   return container_at((container_t*)rb->container, data, rb->tail);
}

size_t rb_size(const ring_buffer_t* rb)
{
    assert(rb);

    return container_size((container_t*)rb->container);
}

bool rb_is_empty(const ring_buffer_t* rb)
{
    assert(rb);

    return (container_size((container_t*)rb->container) == 0);
}

bool rb_is_full(const ring_buffer_t* rb)
{
    assert(rb);

    return (container_size((container_t*)rb->container) >= rb->max_size);
}

bool rb_clear(ring_buffer_t* rb)
{
    assert(rb);
    container_clear((container_t*)rb->container);
}
