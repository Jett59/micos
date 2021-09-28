#ifndef _LOCK_H
#define _LOCK_H

#include <thread.h>
#include <stdint.h>

typedef thread_t lock_t;

static inline void synchronise(lock_t* lock) {
while (1) {
  if (!(*lock)) {
    thread_t current_task_id = current_thread();
    if (!(*lock)) {
      *lock = current_task_id;
      if (*lock == current_task_id) {
        return;
      }
    }
  }
  while (*lock)
    ;
  }
}

static inline void free_lock(lock_t* lock) { *lock = 0; }

#endif