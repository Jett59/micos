#ifndef _SYSCALLS_H
#define _SYSCALLS_H

typedef enum {
  SYSCALL_MESSAGE_POST = 0,
  SYSCALL_MESSAGE_PENDING = 1,
  SYSCALL_MESSAGE_GET = 2
} syscall_code_t;

typedef union {
  u16_t u16;
  message_delivery_status message_status;
} syscall_result_t;

#endif