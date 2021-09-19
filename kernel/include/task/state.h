#ifndef _TASK_STATE_H
#define _TASK_STATE_H

#include <task/registers.h>

typedef struct __attribute__((__packed__)) {
  register_state registers;  // Registers, different for each architecture
  const char* name;
  u32_t id;           // Task id
  u8_t user;          // User mode task?
  u8_t wait, notify;  // Wait and notify semaphores
} task_state;

#endif