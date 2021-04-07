#ifndef _KEYBOARD_KEYS_H
#define _KEYBOARD_KEYS_H  

#include <stdint.h>

typedef struct {
    u16_t code;
    u16_t flags;
    u8_t character;
} key_code;

#endif