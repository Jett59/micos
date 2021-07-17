#include <stdio.h>
#include <keyboard/keycodes.h>
#include <drivers/keyboard/handler.h>

void handle_key_event (key_code code, u8_t action)
{
    if (action) {
        putchar(decode_key_code(code));
    }
}
