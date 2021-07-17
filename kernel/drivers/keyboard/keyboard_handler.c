#include <stdio.h>
#include <keyboard/keycodes.h>
#include <drivers/keyboard/handler.h>
#include <keyboard/control_codes.h>
#include <keyboard/status.h>

static keyboard_status status;

void handle_key_event (key_code code, u8_t action)
{
    if (IS_CONTROL_CODE(code)) {
        if (code == KEYCODE_SHIFT) {
            status.shift_status = action;
        }else if (code == KEYCODE_CONTROL) {
            status.control_status = action;
        }else if (code == KEYCODE_ALT) {
            status.alt_status = action;
        }else if (code == KEYCODE_CAPS_LOCK) {
            status.caps_lock_status ^= action;
        }
    }else {
            if (action) {
            u32_t key_char = decode_key_code(code, status.shift_status ^ (IS_KEY_CODE_ALPHABETIC(code) ? status.caps_lock_status : 0));
            if (key_char == '\t') {
                putchar(' ');
                putchar(' ');
                putchar(' ');
                putchar(' ');
            }else {
                putchar(key_char);
            }
        }
    }
}

keyboard_status get_keyboard_status() {
    return status;
}
