#include <task/registry.h>

#define NUMBER_OF_TASKS  1024

static task_state* tasks [NUMBER_OF_TASKS];

static int size = 1, capacity = NUMBER_OF_TASKS;

static int current;

static task_state default_task = {
    .id = 0
};

task_state* get_current_task_state()
{
    return current ? tasks [current] : &default_task;
}
void register_task_state(task_state* task)
{
    tasks [size] = task;
    task->id = size;
    size = size + 1 > capacity ? size : size + 1;
}
task_state* get_next_task_state()
{
    if (++current >= size) {
        current = 1;
    }
    tasks [current]->registers.r15 = 0x11111111F1F1F1F1;
    return tasks[current];
}
