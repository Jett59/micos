#include <page_tables.h>
#include <paging/frames.h>

#include "blocks.h"

void free(void *ptr) {
  u8_t *working_ptr = ptr;
  working_ptr -= sizeof(size_t);  // overhead
  size_t memblock_size = *((size_t *)working_ptr);
  clean_blocks();
  create_block(
      (memblock_t){.start = working_ptr, .end = working_ptr + memblock_size});
  clean_blocks();
  for (u64_t address =
           (u64_t)(working_ptr + sizeof(size_t) + 4095) / 4096 * 4096;
       address < (u64_t)working_ptr + memblock_size; address += 4096) {
    unmap_page(address / 4096);
  }
}
