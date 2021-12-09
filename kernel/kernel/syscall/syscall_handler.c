#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

void syscall_handler(u32_t code, ...) {
    va_list varargs;
    va_start(varargs, code);
    switch (code) {
        case 101: {
            // Debug trace
            puts("Debug trace");
            break;
        }
        default:
          puts("Unknown syscall number:");
          putdec64(code);
    }
    va_end(varargs);
}
