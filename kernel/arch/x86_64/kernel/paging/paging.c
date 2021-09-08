#include <page_tables.h>
#include <paging/frames.h>

page_table_entry_t* init_page_table_0_0(u16_t page_table_index, page_table_entry_t base)
{
    page_table_entry_t* page_table = allocate_frame();
    page_table_entry_t physical_address = base;
    for (int i = 0; i < 512; i++, physical_address+=4096){
        page_table[i] = physical_address;
    }
    return page_table;
}
page_table_entry_t* init_pdd_0_0 ()
{
    page_table_entry_t* pdd_0_0 = allocate_frame() * 4096;
    page_table_entry_t base = PAGE_PRESENT | PAGE_WRITABLE;
    u16_t i;
    // identity map the first 64 megabytes
    for (i = 0; i < 32; i++) {
        pdd_0_0[i] = (page_table_entry_t)init_page_table_0_0 (i, base) | PAGE_PRESENT | PAGE_WRITABLE;
        base += 1024 * 1024 * 2;
    }
    // put the rest of the page tables in empty so they can be allocated later
    for (; i < 512; i++) {
        pdd_0_0[i] = allocate_frame() * 4096 | PAGE_PRESENT | PAGE_WRITABLE;
    }
    return pdd_0_0;
}
page_table_entry_t* init_pdp0 ()
{
    page_table_entry_t* pdp0 = allocate_frame() * 4096;
    pdp0[0] = (page_table_entry_t)init_pdd_0_0 () | PAGE_PRESENT | PAGE_WRITABLE;
    return pdp0;
}
void init_pml4 ()
{
    page_table_entry_t* pml4 = allocate_frame();
    pml4[0] = (page_table_entry_t)init_pdp0 () | PAGE_PRESENT | PAGE_WRITABLE;
    //recursive mapping of page tables makes them accessible at a fixed virtual address
    pml4 [511] = ((u64_t) & (pml4[0])) | PAGE_PRESENT | PAGE_WRITABLE;
    __asm__ ("movq %0, %%cr3" : : "a"(pml4[511])); // put it in cr4
}
