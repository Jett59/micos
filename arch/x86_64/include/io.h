#ifndef _IO_H
#define _IO_H  

#include <stdint.h>

void outb (u8_t val, u16_t port);
u8_t inb (u16_t port);

void outw (u16_t val, u16_t port);
u16_t inw (u16_t port);

void outl (u32_t val, u16_t port);
u32_t inl (u16_t port);

void io_delay ();

#endif