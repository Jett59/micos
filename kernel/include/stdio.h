#ifndef _STDIO_H
#define _STDIO_H  

#include <stdint.h>

int puts (char * str);
int putchar (char c);

void putnum64 (u64_t num, int regex);
void puthex64 (u64_t num);

#endif