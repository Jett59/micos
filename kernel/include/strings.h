#ifndef _STRINGS_H
#define _STRINGS_H  

#include <stdint.h>

void * memset (void * s, u8_t value, size_t size);
void * memcpy (void * src, void * dst, size_t size);

int strlen(const char* str);
int strcpy(char* dest, const char* src);
int strappend(char* str, char c);

int strlen32(const u32_t* str);
int strcpy32(u32_t* dest, const u32_t* src);
int strappend32(u32_t* str, u32_t n);

#endif