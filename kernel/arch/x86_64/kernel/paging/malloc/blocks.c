#include "blocks.h"

#include <lock.h>
#include <page_tables.h>
#include <strings.h>

// circular buffer for keeping track of blocks
static const int size = 1024;

static memblock_t block_buffer[size];
static u8_t prepared = 0;

static u16_t end = 0;
static u16_t start = 0;

static void memblocks_init(void);

static lock_t block_lock;

void create_block(memblock_t new_block) {
  synchronise(&block_lock);
  int i;
  for (i = start; i < end; i++) {
    memblock_t *block = &(block_buffer[i]);
    if ((u64_t)block->start - 1 == (u64_t)new_block.end) {
      block->start = new_block.start;
      break;
    }
    if ((u64_t)block->end + 1 == (u64_t)new_block.start) {
      block->end = new_block.end;
      break;
    }
  }
  if (i == end) {
    block_buffer[end++] = new_block;
  }
  if (end >= size) {
    end = 0;
  }
  free_lock(&block_lock);
}

void *reserve_block(size_t size) {
  synchronise(&block_lock);
  if (!prepared) {
    memblocks_init();
  }
  for (int i = start; i < end; i++) {
    memblock_t block = block_buffer[i];
            if ((u64_t)(block.start - block.end) >= size) {
            void * result = block.start;
            block.start += size;
            block_buffer [i] = block;
            free_lock(&block_lock);
            return result;
        }
  }
  free_lock(&block_lock);
  return 0;
}

static memblock_t tmp_block_buffer[size];

void clean_blocks() {
  synchronise(&block_lock);
  memcpy(tmp_block_buffer, block_buffer, sizeof(block_buffer));
  u16_t new_start = 0;
  u16_t new_end = 0;
  for (; start < end; start++) {
    if (tmp_block_buffer[start].start - tmp_block_buffer[start].end) {
      block_buffer[new_end] = tmp_block_buffer[start];
      new_end++;
    }
  }
  start = new_start;
  end = new_end;
  free_lock(&block_lock);
}

static void memblocks_init(void) {
  init_pml4();
  block_buffer[end++] =
      (memblock_t){.start = (void *)((1 << 20) * 64 + 0xFFFF800000000000),
                   .end = (void *)((1 << 20) * 512 + 0xFFFF800000000000)};
  prepared = 1;
}
