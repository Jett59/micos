#ifndef _PAGING_MALLOC_BLOCKS_H
#define _PAGING_MALLOC_BLOCKS_H

#include <stdint.h>

typedef struct {
  void* start;
  void* end;
} memblock_t;

void create_block(memblock_t block);
// Reserves the block from the block pool. The block will have enough space to
// fit the specified size, + any required alignment bytes.
void* reserve_block(size_t size, unsigned int alignment);
void clean_blocks();

#endif