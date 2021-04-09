#ifndef _PAGING_MALLOC_BLOCKS_H
#define _PAGING_MALLOC_BLOCKS_H  

#include <stdint.h>

typedef struct {
    void * start;
    void * end;
} memblock_t;

void create_block (memblock_t block);
void * reserve_block (size_t size);
void clean_blocks ();

#endif