#include <page_tables.h>

page_table_entry_t * locate_page_table_entry (u64_t page)
{
    u16_t page_table_index = page % 512;
    page = page >> 9; // remote the previously collected bits
    u16_t page_table = page % 512;
    page = page >> 9; // remove the page table
    u16_t pdd = page % 512;
    page = page >> 9;
    u16_t pdp = page %512;
    return ((page_table_entry_t *)PAGE_TABLE_VIRTUAL_ADDRESS (page_table,pdd,pdp)) + page_table_index;
}

void map_page (u64_t frame, u64_t page_index, page_table_entry_t flags)
{
    page_table_entry_t * destination_page_table = locate_page_table_entry (page_index);
    * destination_page_table = (frame * 4096) | flags;
    invalidate_page_cache (page_index);
}

void unmap_page (u64_t page_index)
{
    page_table_entry_t * entry = locate_page_table_entry (page_index);
    * entry = 0;
    invalidate_page_cache (page_index);
}
