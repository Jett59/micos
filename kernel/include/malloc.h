#ifndef _MALLOC_H
#define _MALLOC_H

#include <stdint.h>

void* malloc(size_t size);
void free(void* ptr);

void* calloc(size_t number, size_t size);

#endif