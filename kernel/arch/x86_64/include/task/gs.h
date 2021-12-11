#ifndef _TASK_GS_H
#define _TASK_GS_H  

typedef struct __attribute__((__packed__)) {
  void* kernel_stack;
  void* user_stack;
} gs_context_t;

#endif