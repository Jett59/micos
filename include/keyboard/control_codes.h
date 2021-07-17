#ifndef _KEYBOARD_CONTROL_CODES_H
#define _KEYBOARD_CONTROL_CODES_H  

#include <keyboard/keycodes.h>

#define IS_CONTROL_CODE(CODE)  (\
CODE == KEYCODE_SHIFT \
|| CODE == KEYCODE_ESCAPE \
|| CODE == KEYCODE_CONTROL \
|| CODE == KEYCODE_ALT \
)

#endif