#include <message.h>
#include <ptrrange.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <syscalls.h>

syscall_result_t syscall_handler(syscall_code_t code, ...) {
  va_list varargs;
  va_start(varargs, code);
  syscall_result_t result = {0};
  switch (code) {
      case SYSCALL_MESSAGE_POST: {
        result.message_status =
            message_post(va_arg(varargs, message_header_t),
                         va_arg(varargs, message_payload_t));
        break;
      }
  case SYSCALL_MESSAGE_PENDING: {
    result.u16 = message_pending();
    break;
  }
  case SYSCALL_MESSAGE_GET: {
    message_t* destination_pointer = va_arg(varargs, message_t*);
    if (IS_USER_MODE_POINTER(destination_pointer)) { // Don't overwrite kernel memory
    message_get(destination_pointer);
    }else {
      puts("The application just tried to compromise the kernel!");
    }
    break;
  }
  default:
    puts("Unknown syscall number:");
    putdec64(code);
  }
  va_end(varargs);
  return result;
}
