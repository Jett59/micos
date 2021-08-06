#include <task/registry.h>
#include <thread.h>

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
    change_current:
    if (++current >= size) {
        current = 1;
    }
    if (tasks [current]->wait) {
        if (tasks [current]->notify) {
            tasks [current]->wait = 0;
            tasks [current].notify = 0;
        }else {
            goto change_current;
        }
    }
    return tasks[current];
}

void wait ()
{
    tasks [current]->wait = 1;
    while (tasks [current]->wait);
}

void notify (thread_t thread)
{
    tasks [thread]->notify = 1;
}
