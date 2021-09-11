#ifndef _MALLOC_H
#define _MALLOC_H  

#include <stdint.h>

void * malloc (size_t size, unsigned int alignment);
void free (void * ptr);

#endif