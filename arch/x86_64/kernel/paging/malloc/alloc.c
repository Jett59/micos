#include <page_tables.h>
#include "blocks.h"

void * malloc (size_t size)
{
    size = ((size >> 12) << 12) + 4096; // page aligned
    void * ptr = reserve_block (size);
    u8_t * working_ptr = ptr;
    for (int i = 0; i < size; i+=4096){
        map_page ((u64_t)(working_ptr + i) >> 12, (u64_t)(working_ptr + i) >> 12, PAGE_PRESENT | PAGE_WRITABLE);
    }
    working_ptr = ptr;
    * ((size_t *)working_ptr) = size;
    working_ptr += sizeof (size_t);
    ptr = working_ptr;
    return ptr;
}
