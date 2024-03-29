#ifndef _PAGE_TABLES_H
#define _PAGE_TABLES_H

#include <paging/constants.h>
#include <stdint.h>

typedef u64_t page_table_entry_t;

typedef u64_t page_table_t[512] __attribute__((aligned(4096)));

void init_pml4();

void map_page(u64_t frame_index, u64_t page_index, page_table_entry_t flags);
void unmap_page(u64_t page_index);

void invalidate_page_cache(u64_t page_index);

// because of recursive mapping, these special addresses point to the various
// parts of the page tables
#define PML4_VIRTUAL_ADDRESS 01777777777777777770000ULL
#define PDP_VIRTUAL_ADDRESS(PDP) (PDP * 010000ULL | 01777777777777770000000ULL)
#define PDD_VIRTUAL_ADDRESS(PDD, PDP)                                          \
  (PDD * 010000ULL | PDP * 010000000ULL | 01777777777770000000000ULL)
#define PAGE_TABLE_VIRTUAL_ADDRESS(PAGE_TABLE, PDD, PDP)                       \
  (PAGE_TABLE * 010000ULL | PDD * 010000000ULL | PDP * 010000000000ULL |       \
   01777777770000000000000ULL)

#endif