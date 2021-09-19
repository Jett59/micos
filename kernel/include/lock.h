#ifndef _LOCK_H
#define _LOCK_H

#include <stdint.h>
#include <task/registry.h>

typedef u32_t lock_t;

static inline void synchronise(lock_t* lock) {
initial_lock_check:
  if (!(*lock)) {
    u32_t current_task_id = get_current_task_state()->id;
    if (!(*lock)) {
      *lock = current_task_id;
      if (*lock == current_task_id) {
        return;
      }
    }
  }
  while (*lock)
    ;
  goto initial_lock_check;
}

static inline void free_lock(lock_t* lock) { *lock = 0; }

#endif