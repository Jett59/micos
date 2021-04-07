#ifndef _PAGE_TABLES_H
#define _PAGE_TABLES_H  

#include <stdint.h>

typedef u64_t page_table_entry_t;

typedef u64_t page_table_t [512] __attribute__ ((aligned (4096)));

#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITABLE (1 << 1)
#define PAGE_USER (1 << 2)
/*we don't use the rest of the flags*/

void init_pml4 ();

#define PML4_VIRTUAL_ADDRESS  01777777777777777770000
#define PDP_VIRTUAL_ADDRESS(I) (I * 01110000 + 01777777777777770000000)

#endif