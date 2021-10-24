#include <error.h>
#include <page_tables.h>
#include <paging/alloc.h>
#include <paging/frames.h>

#include "blocks.h"

void *malloc(size_t size) {
  size = (size + 4095) / 4096 * 4096; // align ed
  void *ptr = reserve_block(size);
  allocate_pages(ptr, size / 4096, PAGE_WRITABLE);
  u8_t *working_ptr = ptr;
  *((size_t *)working_ptr) = size;
  working_ptr += sizeof(size_t);
  ptr = working_ptr;
  return ptr;
}

void *malloc_uncacheable(size_t size) {
  size = (size + 4095) / 4096 * 4096; // align ed
  void *ptr = reserve_block(size);
  allocate_pages(ptr, size / 4096, PAGE_WRITABLE | PAGE_CACHE_DISABLE);
  u8_t *working_ptr = ptr;
  *((size_t *)working_ptr) = size;
  working_ptr += sizeof(size_t);
  ptr = working_ptr;
  return ptr;
}
