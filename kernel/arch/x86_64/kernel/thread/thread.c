#include <thread.h>
#include <task/registry.h>
#include <stdlib.h>
#include <strings.h>

#define THREAD_STACK_SIZE 65536

int create_thread (thread_t* thread, void (*start)(void*), void* arg)
{
    int8_t* stack = malloc(THREAD_STACK_SIZE, 1);
    if (stack == 0) {
        return 1;
    }
    stack += THREAD_STACK_SIZE;
    task_state* task = malloc (sizeof (task_state), 1);
    if (task == 0) {
        return 1;
    }
    memset(task, 0, sizeof (task_state));
    task->registers.rip = start;
    task->registers.rflags = 0x200; // Enable external interrupts
    task->registers.rsp = stack;
    void* cr3;
    __asm__("mov %%cr3, %0" : "=a"(cr3));
    task->registers.cr3 = cr3;
    task->registers.rdi = arg;
    register_task_state(task);
    *thread = task->id;
    return 0;
}
