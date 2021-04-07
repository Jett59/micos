#include <io.h>
#include <stdio.h>
#include <keyboard/keymaps.h>

static key_code default_map [] = STANDARD_QWERTY;

void key_signal (void)
{
    u8_t scan = inb (0x60);
    u16_t action = (scan >> 7) ^ 1; /*1 for pressed, 0 for released*/
    scan = scan & 0x7f; /*just scan code*/
    default_map [scan].flags &= 0xFFFE; //clear bit 0 (state)
    default_map[scan].flags |= action;
    if (action) {
        putchar (default_map[scan].character);
    }
    //send eoi
    u8_t keyboard_state = inb (0x61);
    outb (keyboard_state | 0x80, 0x61);
    outb (keyboard_state, 0x61);
    outb (0x20, 0x20);
}