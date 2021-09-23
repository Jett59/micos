#ifndef _STDIO_H
#define _STDIO_H

#include <stdint.h>

int puts(char* str);
int putchar(char c);

void putnum64(u64_t num, int radix);

static inline void puthex64(u64_t num) { putchar('0');
  putchar('x');
  putnum64(num, 16);
}

static inline void putdec64(u64_t num) { putnum64(num, 10); }

#endif