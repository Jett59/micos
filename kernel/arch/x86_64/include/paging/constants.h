#ifndef _PAGING_CONSTANTS_H
#define _PAGING_CONSTANTS_H

#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITABLE (1 << 1)
#define PAGE_USER (1 << 2)
#define PAGE_WRITE_THROUGH_CACHE (1 << 3)
#define PAGE_CACHE_DISABLE (1 << 4)

#define PAGE_SIZE 4096

#endif