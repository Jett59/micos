#include <error.h>
#include <page_tables.h>
#include <paging/alloc.h>
#include <paging/frames.h>

#include "blocks.h"

void free(void *ptr) {
  u8_t *working_ptr = ptr;
  working_ptr -= sizeof(size_t); // overhead
  if ((u64_t)working_ptr % 4096) {
    fatal_error("Unaligned pointer cannot be freed");
  }
  size_t memblock_size = *((size_t *)working_ptr);
  if (memblock_size % 4096) {
    fatal_error("Corrupted memory passed to free");
  }
  clean_blocks();
  create_block(
      (memblock_t){.start = working_ptr, .end = working_ptr + memblock_size});
  clean_blocks();
  free_pages(working_ptr, memblock_size / 4096);
}
