#ifndef _KEYBOARD_STATUS_H
#define _KEYBOARD_STATUS_H  

#include <stdint.h>

typedef struct {
    u8_t shift_status;
    u8_t control_status;
    u8_t alt_status;
    u8_t caps_lock_status;
} keyboard_status;

keyboard_status get_keyboard_status();

#endif