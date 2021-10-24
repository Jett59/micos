#ifndef _PAGING_ALLOC_H
#define _PAGING_ALLOC_H  

#include <stdint.h>
#include <page_tables.h>
#include <paging/frames.h>

static inline void allocate_pages(const void* address, u64_t pages, page_table_entry_t flags) {
  for (u64_t i = 0; i < pages; i ++) {
    map_page(allocate_frame(), (u64_t)address / 4096 + i, flags | PAGE_PRESENT);
  }
}
static inline void free_pages(const void* address, u64_t pages) {
  for (u64_t i = 0; i < pages; i ++) {
    unmap_page((u64_t)address / 4096 + i);
  } 
}

#endif