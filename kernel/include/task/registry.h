#ifndef _TASK_REGISTRY_H
#define _TASK_REGISTRY_H

#include <task/state.h>

task_state* get_current_task_state(void);
void register_task_state(task_state* task);
task_state* get_next_task_state(void);

#endif