/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "allocator_if.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
queue_t* queue_create(size_t esize)
{
    assert(0 != esize);

    if (!is_allocator_valid())
    {
        return false;
    }

    allocate_fn_t mem_allocate = get_allocator();
    free_fn_t mem_free = get_free();

    queue_t* queue = container_create(esize, CONTAINER_LINKED_LIST_BASED);
    if (NULL == queue)
    {
        return NULL;
    }

    return queue;
}

void queue_delete(queue_t** queue)
{
}

bool queue_get(queue_t* queue, const void* data)
{
    assert(queue);
    assert(data);

    return container_push_front((container_t*)queue, data);
}

bool queue_add(queue_t* queue, void* data)
{
    assert(NULL != queue);
    assert(NULL != data);

    return container_pop_back((container_t*)queue, data);
}

bool queue_peek(const queue_t* queue, void* data)
{
    assert(NULL != queue);
    assert(NULL != data);

    return container_at((container_t*)queue, data, 0);
}

bool queue_size(const queue_t* queue)
{
    return container_size((container_t*)queue);
}