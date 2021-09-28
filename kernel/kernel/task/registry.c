#include <task/registry.h>
#include <thread.h>

#define NUMBER_OF_TASKS 1024

static task_state *tasks[NUMBER_OF_TASKS];

static int size = 1, capacity = NUMBER_OF_TASKS;

static int current = 0;

static task_state default_task = {.id = 0};

static task_state *current_task_state = &default_task;

task_state *get_current_task_state() { return current_task_state; }
void register_task_state(task_state *task) {
  tasks[size] = task;
  task->id = size;
  size = size + 1 > capacity ? size : size + 1;
}
task_state *get_next_task_state() {
change_current:
  if (++current >= size) {
    current = 1;
  }
  if (tasks[current]->wait) {
    if (tasks[current]->notify) {
      tasks[current]->wait = 0;
      tasks[current]->notify = 0;
    } else {
      goto change_current;
    }
  }
  return current_task_state = tasks[current];
}

void wait() {
  tasks[current]->wait = 1;
  while (current_task_state->wait && !current_task_state->notify)
    ;
}

void notify(thread_t thread) { tasks[thread]->notify = 1; }

thread_t current_thread() { return current_task_state->id; }

message_delivery_status message_post(message_header_t header,
                                     message_payload_t payload) {
  if (header.to <= size) {
    task_state *task = tasks[header.to];
    if (task->id) {
      if (task->available_messages) {
        synchronise(&task->message_lock);
        if (task->available_messages) {
          task->available_messages--;
          u16_t slot = task->message_end++;
          if (task->message_end >= MESSAGE_BUFFER_LENGTH) {
            task->message_end = 0;
          }
          task->messages[slot] =
              (message_t){.header = header, .payload = payload};
          task->pending_messages++;
          free_lock(&task->message_lock);
          notify(task->id);
          return MESSAGE_DELIVERED;
        } else {
          free_lock(&task->message_lock);
          return MESSAGE_TARGET_BUSY;
        }
      } else {
        return MESSAGE_TARGET_BUSY;
      }
    } else {
      return MESSAGE_TARGET_NOT_FOUND;
    }
  } else {
    return MESSAGE_TARGET_NOT_FOUND;
  }
}

u16_t message_pending() { return current_task_state->pending_messages; }

void message_get(message_t *message) {
  while (!message_pending()) {
    wait();
  }
  u16_t slot = current_task_state->message_start++;
  if (current_task_state->message_start > MESSAGE_BUFFER_LENGTH) {
    current_task_state->message_start = 0;
  }
  *message = current_task_state->messages[slot];
  synchronise(&current_task_state->message_lock);
  current_task_state->pending_messages--;
  current_task_state->available_messages++;
  free_lock(&current_task_state->message_lock);
}
