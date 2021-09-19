#include <drivers/keyboard/handler.h>
#include <io.h>
#include <keyboard/keycodes.h>

// Default US qwerty keymap

#define STANDARD_QWERTY                                                       \
  {                                                                           \
    KEYCODE_NONE, KEYCODE_ESCAPE, KEYCODE_1, KEYCODE_2, KEYCODE_3, KEYCODE_4, \
        KEYCODE_5, KEYCODE_6, KEYCODE_7, KEYCODE_8, KEYCODE_9, KEYCODE_0,     \
        KEYCODE_DASH, KEYCODE_EQUALS, KEYCODE_BACKSPACE, KEYCODE_TAB,         \
        KEYCODE_Q, KEYCODE_W, KEYCODE_E, KEYCODE_R, KEYCODE_T, KEYCODE_Y,     \
        KEYCODE_U, KEYCODE_I, KEYCODE_O, KEYCODE_P, KEYCODE_LEFT_BRACKET,     \
        KEYCODE_RIGHT_BRACKET, KEYCODE_ENTER, KEYCODE_CONTROL, KEYCODE_A,     \
        KEYCODE_S, KEYCODE_D, KEYCODE_F, KEYCODE_G, KEYCODE_H, KEYCODE_J,     \
        KEYCODE_K, KEYCODE_L, KEYCODE_SEMICOLON, KEYCODE_QUOTE,               \
        KEYCODE_BACKTICK, KEYCODE_SHIFT, KEYCODE_BACKSLASH, KEYCODE_Z,        \
        KEYCODE_X, KEYCODE_C, KEYCODE_V, KEYCODE_B, KEYCODE_N, KEYCODE_M,     \
        KEYCODE_COMMA, KEYCODE_DOT, KEYCODE_SLASH, KEYCODE_SHIFT,             \
        KEYCODE_UNDEFINED, KEYCODE_ALT, KEYCODE_SPACE, KEYCODE_CAPS_LOCK      \
  }

static key_code default_map[] = STANDARD_QWERTY;

void key_signal(void) {
  u8_t scan = inb(0x60);
  u8_t action = (scan >> 7) ^ 1; /*1 for pressed, 0 for released*/
  scan = scan & 0x7f;            /*just scan code*/
  handle_key_event(default_map[scan], action);
  // send eoi
  u8_t keyboard_state = inb(0x61);
  outb(keyboard_state | 0x80, 0x61);
  outb(keyboard_state, 0x61);
  outb(0x20, 0x20);
}