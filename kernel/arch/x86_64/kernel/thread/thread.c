#include <stdlib.h>
#include <strings.h>
#include <task/registry.h>
#include <thread.h>

#define THREAD_STACK_SIZE 65536

int create_thread(thread_t *thread, void (*start)(void *), void *arg,
                  const char *name, bool user_mode) {
  u8_t *stack = malloc(THREAD_STACK_SIZE);
  if (stack == 0) {
    return 1;
  }
  stack += THREAD_STACK_SIZE;
  task_state *task = malloc(sizeof(task_state));
  if (task == 0) {
    return 1;
  }
  memset(task, 0, sizeof(task_state));
  if (!user_mode) {
    task->registers.rsp = (u64_t)stack;
  }
  task->registers.gs_context.kernel_stack = stack;
  task->registers.alternate_gs = (u64_t)&task->registers.gs_context;
  task->name = name;
  task->registers.rip = (u64_t)start;
  task->registers.rflags = 0x200; // Enable external interrupts
  void *cr3;
  __asm__("mov %%cr3, %0" : "=a"(cr3));
  task->registers.cr3 = (u64_t)cr3;
  task->registers.rdi = (u64_t)arg;
  if (user_mode) {
    task->registers.cs = 48 | 3; // User mode (48) | 3 (destination privilege level)
    task->registers.ss = 40 | 3; // Stack segment (40) | 3 (user mode)
  } else {
    task->registers.cs = 8;
  }
  register_task_state(task);
  *thread = task->id;
  return 0;
}
