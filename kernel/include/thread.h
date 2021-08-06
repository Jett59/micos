#ifndef _THREAD_H
#define _THREAD_H  

#include <stdint.h>

typedef u32_t thread_t;

int create_thread(thread_t* thread, void (*start)(void*), void* arg);

// Waits until a call to notify () with the current thread id
void wait ();

void notify (thread_t thread);

#endif