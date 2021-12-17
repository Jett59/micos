#ifndef _TASK_STATE_H
#define _TASK_STATE_H

#include <task/registers.h>
#include <lock.h>
#include <message.h>

typedef struct {
  register_state registers;
  const char* name;
  u16_t id;
  u8_t wait, notify;
  lock_t message_lock;
  u16_t message_start, message_end, available_messages, pending_messages;
  message_t messages[MESSAGE_BUFFER_LENGTH];
} task_state;

#endif