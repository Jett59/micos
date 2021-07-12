#ifndef _MEMORY_H
#define _MEMORY_H

#include <stdint.h>

void* map_physical_address(void* physical_address, size_t size);

#endif