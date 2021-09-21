#include <malloc.h>
#include <memory.h>
#include <page_tables.h>
#include <paging/frames.h>

page_table_entry_t *locate_page_table_entry(u64_t page) {
  u16_t page_table_index = page % 512;
  page = page >> 9;  // remove the previously collected bits
  u16_t page_table = page % 512;
  page = page >> 9;  // remove the page table
  u16_t pdd = page % 512;
  page = page >> 9;
  u16_t pdp = page % 512;
  return ((page_table_entry_t *)PAGE_TABLE_VIRTUAL_ADDRESS(page_table, pdd,
                                                           pdp)) +
         page_table_index;
}

void toggle_flags(u64_t page_index, page_table_entry_t flags) {
  page_table_entry_t *destination_page_table =
      locate_page_table_entry(page_index);
  *destination_page_table ^= flags;
  invalidate_page_cache(page_index);
}

void map_page(u64_t frame, u64_t page_index, page_table_entry_t flags) {
  page_table_entry_t *destination_page_table =
      locate_page_table_entry(page_index);
  *destination_page_table = (frame * 4096) | flags;
  invalidate_page_cache(page_index);
}

void unmap_page(u64_t page_index) {
  page_table_entry_t *entry = locate_page_table_entry(page_index);
  u64_t frame_index =
      (*entry >> 12) & 0xFFFFFFFFFFFF;  // 52 bit address, remove the flags
  return_frame(frame_index);
  *entry = 0;
  invalidate_page_cache(page_index);
}

void *map_physical_address(void *address, size_t size) {
  u64_t pages = (size + 4095) / 4096;
  void *ptr = malloc(pages * 4096, 4096);
  u64_t frame_index = ((u64_t)address) / 4096;
  u64_t page_index = ((u64_t)ptr) / 4096;
  reserve_frames(frame_index, frame_index + pages - 1);
  for (u64_t i = 0; i < pages; i++) {
    map_page(frame_index + i, page_index + i, PAGE_PRESENT | PAGE_WRITABLE);
  }
  return (void *)(page_index * 4096 + ((u64_t)address % 4096));
}
void *map_physical_address_uncached(void *physical_address, size_t size) {
  void *ptr = map_physical_address(physical_address, size);
  u64_t pages = (size + 4095) / 4096;  // page aligned
  u64_t page_index = ((u64_t)ptr) / 4096;
  for (int i = 0; i < pages; i++) {
    toggle_flags(page_index + i, PAGE_CACHE_DISABLE);
  }
  return ptr;
}
