#ifndef _KEYBOARD_KEYCODES_H
#define _KEYBOARD_KEYCODES_H  

#include <keyboard/keys.h>

#define KEYCODE_0  0x0
#define KEYCODE_1  0x1
#define KEYCODE_2  0x2
#define KEYCODE_3  0x3
#define KEYCODE_4  0x4
#define KEYCODE_5  0x5
#define KEYCODE_6  0x6
#define KEYCODE_7  0x7
#define KEYCODE_8  0x8
#define KEYCODE_9  0x9
#define KEYCODE_A  0xA
#define KEYCODE_B  0xB
#define KEYCODE_C  0xC
#define KEYCODE_D  0xD
#define KEYCODE_E  0xE
#define KEYCODE_F  0xF
#define KEYCODE_G  0x10
#define KEYCODE_H  0x11
#define KEYCODE_I  0x12
#define KEYCODE_J  0x13
#define KEYCODE_K  0x14
#define KEYCODE_L  0x15
#define KEYCODE_M  0x16
#define KEYCODE_N  0x17
#define KEYCODE_O  0x18
#define KEYCODE_P  0x19
#define KEYCODE_Q  0x1A
#define KEYCODE_R  0x1B
#define KEYCODE_S  0x1C
#define KEYCODE_T  0x1D
#define KEYCODE_U  0x1E
#define KEYCODE_V  0x1F
#define KEYCODE_W  0x20
#define KEYCODE_X  0x21
#define KEYCODE_Y  0x22
#define KEYCODE_Z  0x23

#define KEYCODE_ENTER  0x24
#define KEYCODE_SPACE  0x25
#define KEYCODE_COMMA  0x26
#define KEYCODE_DOT  0x27
#define KEYCODE_SLASH  0x28
#define KEYCODE_SEMICOLON  0x29
#define KEYCODE_QUOTE  0x2A

#define KEYCODE_UNDEFINED  0xFFFE
#define KEYCODE_NONE  0xFFFF

u32_t decode_key_code(key_code code);

#endif