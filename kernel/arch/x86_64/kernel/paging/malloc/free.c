#include "blocks.h"
#include <page_tables.h>

void free (void * ptr)
{
    u8_t * working_ptr = ptr;
    working_ptr -= sizeof (size_t); // overhead
    if ((u64_t)working_ptr % 4096) {
        __asm__ ("int $0x1D"); // #pf if memory area is not page aligned
    }
    size_t memblock_size = * ((size_t *)working_ptr);
    if (memblock_size % 4096) {
        __asm__ ("int $0x1D"); // #pf if size is not page aligned
    }
    clean_blocks ();
    create_block ((memblock_t){
        .start = working_ptr, 
        .end = working_ptr + memblock_size
    });
    clean_blocks ();
    for (u64_t address = (u64_t)working_ptr; address < (u64_t)working_ptr + memblock_size; address+=4096) {
        unmap_page (address / 4096);
    }
}
