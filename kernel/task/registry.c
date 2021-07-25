#include <task/registry.h>

#define NUMBER_OF_TASKS  1024

static task_state* tasks [NUMBER_OF_TASKS];

static int size = 1, capacity = NUMBER_OF_TASKS;

static int current;

task_state* get_current_task_state()
{
    return tasks [current];
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
    return tasks[current];
}
