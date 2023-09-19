/**
 * @file iterator.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

//_____ I N C L U D E S _______________________________________________________
#include "iterator.h"

#include "interface/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct Iterator_tag
{
  void* container;
  size_t current_index;
  size_t size;
};
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
#if 0
iterator_t* iterator_create(const container_t* container, bool is_move)
{
    assert(container);

    allocate_fn_t mem_allocate = get_allocator();
    assert(mem_allocate);

    iterator_t* iterator = (iterator_t*)mem_allocate(sizeof(iterator_t));
    if (NULL == iterator)
    {
        return NULL;
    }

    iterator->container = container;
    iterator->current_index = 0;
    iterator->size = container_size(container);
}

void iterator_delete(iterator_t** iterator)
{

}

bool iterator_next(const iterator_t* iterator)
{
    return (iterator->size != iterator->current_index);
}

bool iterator_get(const iterator_t* iterator, void* data)
{
    assert(iterator);
    assert(data);

    bool status = container_at(iterator->container, data, iterator->current_index);
    if(!status)
    {
        return false;
    }

    iterator->current_index++;

    return true;
}
#endif
