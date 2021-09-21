#include <error.h>
#include <page_tables.h>
#include <paging/frames.h>

#include "blocks.h"

void *malloc(size_t size, unsigned int alignment) {
  size = (size + alignment - 1 + 8); // align ed
  void *ptr = reserve_block(size, alignment);
  u8_t *working_ptr = ptr;
  u64_t first_page = ((u64_t)working_ptr + 4095) / 4096 * 4096;
  u64_t last_page = first_page + (size + 4095) / 4096 * 4096;
  for (u64_t i = first_page; i <= last_page; i += 4096) {
    map_page(allocate_frame(), i >> 12, PAGE_PRESENT | PAGE_WRITABLE);
  }
  working_ptr = ptr;
  *((size_t *)working_ptr) = size;
  working_ptr += sizeof(size_t);
  ptr = working_ptr;
  return ptr;
}

void *malloc_uncacheable(size_t size, unsigned int alignment) {
  size = (size + alignment - 1 + 8); // aligned
  void *ptr = reserve_block(size, alignment);
  u8_t *working_ptr = ptr;
  u64_t first_page = ((u64_t)working_ptr + 4095) / 4096 * 4096;
  u64_t last_page = first_page + (size + 4095) / 4096 * 4096;
  for (u64_t i = first_page; i <= last_page; i += 4096) {
    map_page(allocate_frame(), i >> 12,
             PAGE_PRESENT | PAGE_WRITABLE | PAGE_CACHE_DISABLE);
  }
  working_ptr = ptr;
  *((size_t *)working_ptr) = size;
  working_ptr += sizeof(size_t);
  ptr = working_ptr;
  return ptr;
}
