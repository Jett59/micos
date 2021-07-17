#include <keyboard/keycodes.h>

static u32_t keycode_chars_lowercase [] = {
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
    [KEYCODE_COMMA] = ',',
    [KEYCODE_DOT] = '.',
    [KEYCODE_SLASH] = '/',
    [KEYCODE_SEMICOLON] = ';',
    [KEYCODE_QUOTE] = '\'',
    [KEYCODE_DASH] = '-',
    [KEYCODE_EQUALS] = '=',
    [KEYCODE_LEFT_BRACKET] = '[',
    [KEYCODE_RIGHT_BRACKET] = ']',
    [KEYCODE_BACKSLASH] = '\\',
    [KEYCODE_BACKTICK] = '`',
    [KEYCODE_BACKSPACE] = 0x08,
    [KEYCODE_UNDEFINED] = 0,
    [KEYCODE_NONE] = 0
};

static u32_t keycode_chars_uppercase [] = {
    [KEYCODE_0] = ')',
    [KEYCODE_1] = '!',
    [KEYCODE_2] = '@',
    [KEYCODE_3] = '#',
    [KEYCODE_4] = '$',
    [KEYCODE_5] = '%',
    [KEYCODE_6] = '^',
    [KEYCODE_7] = '&',
    [KEYCODE_8] = '*',
    [KEYCODE_9] = '(',
    [KEYCODE_A] = 'A',
    [KEYCODE_B] = 'B',
    [KEYCODE_C] = 'C',
    [KEYCODE_D] = 'D',
    [KEYCODE_E] = 'E',
    [KEYCODE_F] = 'F',
    [KEYCODE_G] = 'G',
    [KEYCODE_H] = 'H',
    [KEYCODE_I] = 'I',
    [KEYCODE_J] = 'J',
    [KEYCODE_K] = 'K',
    [KEYCODE_L] = 'L',
    [KEYCODE_M] = 'M',
    [KEYCODE_N] = 'N',
    [KEYCODE_O] = 'O',
    [KEYCODE_P] = 'P',
    [KEYCODE_Q] = 'Q',
    [KEYCODE_R] = 'R',
    [KEYCODE_S] = 'S',
    [KEYCODE_T] = 'T',
    [KEYCODE_U] = 'U',
    [KEYCODE_V] = 'V',
    [KEYCODE_W] = 'W',
    [KEYCODE_X] = 'X',
    [KEYCODE_Y] = 'Y',
    [KEYCODE_Z] = 'Z',
    [KEYCODE_ENTER] = '\n',
    [KEYCODE_SPACE] = ' ',
    [KEYCODE_COMMA] = '<',
    [KEYCODE_DOT] = '>',
    [KEYCODE_SLASH] = '?',
    [KEYCODE_SEMICOLON] = ':',
    [KEYCODE_QUOTE] = '\"',
    [KEYCODE_DASH] = '_',
    [KEYCODE_EQUALS] = '+',
    [KEYCODE_LEFT_BRACKET] = '{',
    [KEYCODE_RIGHT_BRACKET] = '}',
    [KEYCODE_BACKSLASH] = '|',
    [KEYCODE_BACKTICK] = '~',
    [KEYCODE_BACKSPACE] = 0x08,
    [KEYCODE_UNDEFINED] = 0,
    [KEYCODE_NONE] = 0
};

u32_t decode_key_code(key_code code, u8_t uppercase)
{
    if (uppercase) {
        return keycode_chars_uppercase [code];
    }else {
        return keycode_chars_lowercase [code];
    }
}
