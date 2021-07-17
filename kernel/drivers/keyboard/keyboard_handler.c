#include <stdio.h>
#include <keyboard/keycodes.h>
#include <drivers/keyboard/handler.h>
#include <keyboard/control_codes.h>

static u8_t shift_status = 0;

void handle_key_event (key_code code, u8_t action)
{
    if (IS_CONTROL_CODE(code)) {
        if (code == KEYCODE_SHIFT) {
            shift_status = action;
        }
    }else {
            if (action) {
            u32_t key_char = decode_key_code(code, shift_status);
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
