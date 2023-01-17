/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "container.h"

#include <assert.h>

#include "allocator_if.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Container_tag
{
#if CONTAINER_TYPE == LINKED_LIST
    linked_list_t* core;
#elif CONTAINER_TYPE == VECTOR
    vector_t* core;
#endif
};
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
void container_init(allocate_fn_t alloc_cb, free_fn_t free_cb)
{
    assert(alloc_cb);
    assert(free_cb);

    allocation_cb_register(alloc_cb);
    free_cb_register(free_cb);
}

container_t* container_create(size_t esize)
{
    assert(0 != esize);

    if (!is_allocator_valid())
    {
        return false;
    }

    allocate_fn_t mem_allocate = get_allocator();
    free_fn_t mem_free = get_free();

    container_t* container = (container_t*)mem_allocate(sizeof(container_t));
    if (container == NULL)
    {
        return NULL;
    }

#if CONTAINER_TYPE == LINKED_LIST
    container->core = linked_list_create(esize);
#elif CONTAINER_TYPE == VECTOR
    container->core = vector_create(esize);
#endif

    if (container->core == NULL)
    {
        mem_free(container);
        return NULL;
    }

    return container;
}

container_t* container_from_array(void *arr, size_t size, size_t esize)
{
    assert(0 != esize);
    assert(0 != size);
    assert(arr);
 
    container_t* container = container_create(esize);
    if(NULL == container)
    {
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        container_push_back(container, ((uint8_t*)arr + i*esize));
    }
   
    return container;
}



void container_delete(container_t** list)
{
}

bool container_push_front(container_t* container, const void* data)
{
    assert(container);
    assert(data);

    return container->core->push_front(container->core, data);
}

bool container_pop_front(container_t* container, void* data)
{
    assert(container);
    assert(data);

    return container->core->pop_front(container->core, data);
}

bool container_push_back(container_t* container, const void* data)
{
    assert(container);
    assert(data);

    return container->core->push_back(container->core, data);
}

bool container_pop_back(container_t* container, void* data)
{
    assert(container);
    assert(data);

    return container->core->pop_back(container->core, data);
}

bool container_insert(container_t* container, const void* data, size_t position)
{
    assert(container);
    assert(data);

    return container->core->insert(container->core, data, position);
}

bool container_at(const container_t* container, void* data, size_t position)
{
    assert(container);
    assert(data);

    return container->core->at(container->core, data, position);
}

bool container_erase(container_t* container, size_t position)
{
    assert(container);

    return container->core->erase(container->core, position);
}

size_t container_size(const container_t* container)
{
    assert(container);

    return container->core->size(container->core);
}