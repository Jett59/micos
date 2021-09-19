#ifndef _POINTERS_H
#define _POINTERS_H

#include <stdint.h>

void* get_pointer(size_t linear_address);

size_t get_linear_address(void* ptr);

#endif