#ifndef _THREAD_H
#define _THREAD_H  

#include <stdint.h>

int create_thread(u32_t* id, void (*start)(void*), void* arg);

#endif