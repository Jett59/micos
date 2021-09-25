#include <error.h>
#include <page_tables.h>
#include <paging/frames.h>

#include "blocks.h"

void *malloc(size_t size) {
  size = (size + 4095) / 4096 * 4096; // align ed
  void *ptr = reserve_block(size);
  u8_t *working_ptr = ptr;
  for (u64_t i = 0; i < size; i += 4096) {
    map_page(allocate_frame(), (u64_t)(working_ptr + i) >> 12,
             PAGE_PRESENT | PAGE_WRITABLE);
  }
  working_ptr = ptr;
  *((size_t *)working_ptr) = size;
  working_ptr += sizeof(size_t);
  ptr = working_ptr;
  return ptr;
}

void *malloc_uncacheable(size_t size) {
  size = (size + 4095) / 4096 * 4096; // align ed
  void *ptr = reserve_block(size);
  u8_t *working_ptr = ptr;
  for (u64_t i = 0; i < size; i += 4096) {
    map_page(allocate_frame(), (u64_t)(working_ptr + i) >> 12,
             PAGE_PRESENT | PAGE_WRITABLE | PAGE_CACHE_DISABLE);
  }
  working_ptr = ptr;
  *((size_t *)working_ptr) = size;
  working_ptr += sizeof(size_t);
  ptr = working_ptr;
  return ptr;
}
