#include <page_tables.h>

void invalidate_page_cache (u64_t page_index)
{
    __asm__ ("invlpg (%0)" : : "r"(page_index << 11) : "memory");
}