#include <page_tables.h>

static page_table_t pml4;
static page_table_t pdp0;
static page_table_t pdd0_0;
static page_table_t page_tables_0_0 [512];

page_table_entry_t init_page_table_0_0(u16_t page_table_index, page_table_entry_t base)
{
    page_table_entry_t physical_address = base;
    for (int i = 0; i < 512; i++, physical_address+=4096){
        page_tables_0_0[page_table_index][i] = physical_address;
    }
    return physical_address;
}
void init_pdd_0_0 ()
{
    page_table_entry_t base = PAGE_PRESENT | PAGE_WRITABLE;
    for (u16_t i = 0; i < 32; i++) {
        base = init_page_table_0_0 (i, base);
        pdd0_0 [i] = (u64_t)(& (page_tables_0_0[i][0])) | PAGE_PRESENT | PAGE_WRITABLE;
    }
}
void init_pdp0 ()
{
    init_pdd_0_0 ();
    pdp0[0] = ((u64_t) & (pdd0_0[0])) | PAGE_PRESENT | PAGE_WRITABLE;
}
void init_pml4 ()
{
    init_pdp0 ();
    pml4 [0] = ((u64_t) & (pdp0[0])) | PAGE_PRESENT | PAGE_WRITABLE;
    //recursive mapping of page tables makes them accessible at a fixed virtual address
    pml4 [511] = ((u64_t) & (pml4[0])) | PAGE_PRESENT | PAGE_WRITABLE;
    __asm__ ("movq %0, %%cr3" : : "a"(pml4[511])); // put it in cr4
}
