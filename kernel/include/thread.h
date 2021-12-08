#ifndef _THREAD_H
#define _THREAD_H

#include <stdbool.h>
#include <stdint.h>

typedef u16_t thread_t;

int create_thread(thread_t* thread, void (*start)(void*), void* arg,
                  const char* name, bool user_mode);

// Waits until a call to notify () with the current thread id
void wait();

void notify(thread_t thread);

thread_t current_thread();

#endif