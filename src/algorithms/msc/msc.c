/**
 * @file
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-25
 */

//_____ I N C L U D E S _______________________________________________________
#include "msc.h"

#include <assert.h>
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
bool from_array(container_t* container, void *arr, size_t size, size_t esize)
{
    assert(container);
    assert(arr);

    for (size_t i = 0; i < size; i++)
    {
        bool status = container_push_back(container, (void*)(arr + (esize * i)));
        if(!status)
        {
            return false;
        }
    }

    return true;
}

bool to_array(const container_t* container, void *arr, size_t arr_size, size_t esize)
{
    assert(container);
    assert(arr);

    size_t size = container_size(container);
    size_t len = (size >= arr_size) ? arr_size : size;

    for (size_t i = 0; i < len; i++)
    {
        bool status = container_at(container, (arr + (esize * i)), i);
        if(!status)
        {
            return false;
        }
    }

    return true;
}

void to_string(const container_t* container, char* string)
{

}


bool unique(container_t* container)
{

}

bool fill(container_t* container, size_t start, size_t end, void* value)
{

}

container_t* reverse(container_t* container)
{

}