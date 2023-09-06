/**
 * @file set.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-02-01
 */

//_____ I N C L U D E S _______________________________________________________
#include "set.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "allocator_if.h"
#include "container.h"
//_____ C O N F I G S  ________________________________________________________
// #define HASH_INIT_VALUE     5381
#define HASH_INIT_VALUE     0x538155AA
//_____ D E F I N I T I O N S _________________________________________________
#define INVALID_ENTRY          ((void*)(-1))
#define FREE_ENTRY             0
#define BUSY_ENTRY             1

typedef int* entry_bf_t;

/**
*  \brief
*/
struct Set_tag
{
    container_t* container;

    struct
    {
        size_t esize;
        size_t max_size;
        size_t size;
        void* tmp;
    };

    struct
    {
        bool (*equal)(void*, void*);
    };
};

//_____ M A C R O S ___________________________________________________________
#define MAKE_TMP_BUSY(set)\
                            do{\
                                int* is_busy = (set->tmp + set->esize);\
                                *is_busy = 1;\
                            }while(0)

#define MAKE_TMP_FREE(set)\
                            do{\
                                int* is_busy = (set->tmp + set->esize);\
                                *is_busy = 0;\
                            }while(0)

#define MAKE_ENTRY_BUSY_FLAG(base, offset)    (((int*)(base + offset)))
#define IS_ENTRY_FREE(ENTRY_FLAG)    (*ENTRY_FLAG == FREE_ENTRY)
//_____ V A R I A B L E S _____________________________________________________

//_____ P R I V A T E  F U N C T I O N S_______________________________________
static uint32_t fnv_hash_32(const char *data, size_t len)
{
    #define FNV_PRIME_32 16777619
    #define FNV_OFFSET_BASIS_32 2166136261

    uint32_t hash = FNV_OFFSET_BASIS_32;
    for (size_t i = 0; i < len; i++) {
        hash = hash * FNV_PRIME_32;
        hash = hash ^ data[i];
    }
    return hash;
}

uint32_t djb2_hash(const char *data, size_t len)
{
    uint32_t hash = 5381;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + data[i];
    }
    return hash;
}

static uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;
    static const uint32_t r1 = 15;
    static const uint32_t r2 = 13;
    static const uint32_t m = 5;
    static const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *) key;
    int i;
    for (i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3) {
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0];

        k1 *= c1;
        k1 = (k1 << r1) | (k1 >> (32 - r1));
        k1 *= c2;
        hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

static size_t hash(void* key, size_t esize, size_t attempt, size_t max_size)
{
    uint32_t hash = murmur3_32((uint8_t*) key, esize, attempt + HASH_INIT_VALUE);

    return hash % max_size;
}

static bool resize_container(set_t* set, size_t new_size)
{
    size_t current_size = container_size(set->container);
    if(current_size >= new_size)
    {
        return true;
    }

    memset(set->tmp, 0, (set->esize + sizeof(int)));

    for (size_t i = current_size; i < new_size; i++)
    {
        if(!container_push_back(set->container, set->tmp))
        {
            return false;
        }
    }

    return true;
}

static bool find_duplicate(const set_t* set, const void* data, size_t* index)
{
    assert(set);
    assert(data);

    size_t attempt = 0;
    void* entry = INVALID_ENTRY;
    size_t current_index = hash(data, set->esize, attempt, set->max_size);

    while (entry != NULL || attempt <= set->max_size)
    {
        *index = current_index;

		entry = container_peek(set->container, current_index);
        if(entry == NULL)
        {
            return false;
        }

        entry_bf_t busy_flag = MAKE_ENTRY_BUSY_FLAG(entry, set->esize);

        if(IS_ENTRY_FREE(busy_flag))
        {
            return false;
        }

        if(set->equal(entry, data))
        {
            *index = current_index;
            return true;
        }


        attempt++;
        current_index = hash(data, set->esize, (attempt * attempt), set->max_size);
    }

	return false;
}

static inline void* make_entry(set_t* set, void* data)
{
    memcpy(set->tmp, data, set->esize);
    MAKE_TMP_BUSY(set);
    return set->tmp;
}

static inline bool is_empty(set_t* set)
{
    return set->size == 0;
}

static inline bool is_full(set_t* set)
{
    return set->size >= (set->max_size - (set->max_size * 0.3));
}
//_____ P U B L I C  F U N C T I O N S_________________________________________
set_t* set_create(size_t max_size, size_t esize, bool (*equal)(void*, void*))
{
    assert(0 != esize);
    assert(0 != max_size);

    if (!is_allocator_valid())
    {
        return NULL;
    }

    allocate_fn_t mem_allocate = get_allocator();

    set_t* set = (set_t*)mem_allocate(sizeof(set_t));
    if (NULL == set)
    {
        return NULL;
    }

    set->container = container_create((esize + sizeof(int)), CONTAINER_VECTOR_BASED);
    if(set->container == NULL)
    {
        return NULL;
    }

    // set->max_size = max_size;
    set->max_size = (max_size * 0.3) + max_size;
    set->esize = esize;
    set->size = 0;
    set->equal = equal;

    set->tmp = (void*)mem_allocate((esize + sizeof(int)));
    if (set->tmp == NULL)
    {
        return NULL;
    }

    if(!resize_container(set, max_size))
    {
        return false;
    }

    return set;
}

void set_delete(set_t* set)
{
    assert(set);

    free_fn_t mem_free = get_free();
    assert(mem_free);

    mem_free(set->tmp);
    container_delete(set->container);
    mem_free(set);
}

bool set_add(set_t* set, void* data)
{
    assert(set);
    assert(data);

    if(is_full(set))
    {
        return false;
    }

    bool status = false;
    size_t index = 0;

    if (!find_duplicate(set, data, &index))
    {
        status = container_replace(set->container, make_entry(set, data), index);
        if(status)
        {
            set->size++;
        }
    }

    return status;
}

bool set_remove(set_t* set, void* data)
{
    assert(set);
    assert(data);

    if(is_empty(set))
    {
        return false;
    }

    bool status = false;
    size_t index = 0;

    if(!find_duplicate(set, data, &index))
    {
        return false;
    }

    MAKE_TMP_FREE(set);
    status = container_replace(set->container, set->tmp, index);
    if(status)
    {
        set->size--;
    }

    return status;
}

bool set_contain(set_t* set, void* data)
{
    assert(0 != set);
    assert(0 != data);

    if(set->size == 0)
    {
        return false;
    }

    size_t index = 0;
    return find_duplicate(set, data, &index);
}

size_t set_size(set_t* set)
{
    assert(0 != set);

    return set->size;
}
