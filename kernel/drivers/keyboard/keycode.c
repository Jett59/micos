#include <keyboard/keycodes.h>

static u32_t keycode_chars [] = {
    [KEYCODE_0] = '0',
    [KEYCODE_1] = '1',
    [KEYCODE_2] = '2',
    [KEYCODE_3] = '3',
    [KEYCODE_4] = '4',
    [KEYCODE_5] = '5',
    [KEYCODE_6] = '6',
    [KEYCODE_7] = '7',
    [KEYCODE_8] = '8',
    [KEYCODE_9] = '9',
    [KEYCODE_A] = 'a',
    [KEYCODE_B] = 'b',
    [KEYCODE_C] = 'c',
    [KEYCODE_D] = 'd',
    [KEYCODE_E] = 'e',
    [KEYCODE_F] = 'f',
    [KEYCODE_G] = 'g',
    [KEYCODE_H] = 'h',
    [KEYCODE_I] = 'i',
    [KEYCODE_J] = 'j',
    [KEYCODE_K] = 'k',
    [KEYCODE_L] = 'l',
    [KEYCODE_M] = 'm',
    [KEYCODE_N] = 'n',
    [KEYCODE_O] = 'o',
    [KEYCODE_P] = 'p',
    [KEYCODE_Q] = 'q',
    [KEYCODE_R] = 'r',
    [KEYCODE_S] = 's',
    [KEYCODE_T] = 't',
    [KEYCODE_U] = 'u',
    [KEYCODE_V] = 'v',
    [KEYCODE_W] = 'w',
    [KEYCODE_X] = 'x',
    [KEYCODE_Y] = 'y',
    [KEYCODE_Z] = 'z',
    [KEYCODE_ENTER] = '\n',
    [KEYCODE_SPACE] = ' ',
    [KEYCODE_UNDEFINED] = 0,
    [KEYCODE_NONE] = 0
};

u32_t decode_key_code(key_code code)
{
    return keycode_chars[code];
}
