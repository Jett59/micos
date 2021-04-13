#ifndef _VGA_CONSOLE_H
#define _VGA_CONSOLE_H  

#include <stdint.h>

#define VGA_TEXT_BUFFER  0xB8000

#define VGA_WIDTH  80
#define VGA_HEIGHT  25

#include <stdint.h>

typedef u8_t conmode_t;

#define STDOUT  0x02
#define STDERR  0x04
#define STDIN  0x0F

typedef struct __attribute__ ((__packed__)) {
    char c;
    conmode_t mode;
} vga_text_cell;

void vga_print_char (char c, conmode_t mode);

#endif