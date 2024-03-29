#include <hault.h>
#include <task/registry.h>
#include <thread.h>

#define NUMBER_OF_TASKS 1024

static task_state *tasks[NUMBER_OF_TASKS];

static int size = 1, capacity = NUMBER_OF_TASKS;

static int current = 0;

static task_state default_task = {.id = 0, .name = "<Bootstrap>"};

static task_state *current_task_state = &default_task;

task_state *get_current_task_state(void) { return current_task_state; }

void register_task_state(task_state *task) {
  tasks[size] = task;
  task->id = size;
  task->available_messages = MESSAGE_BUFFER_LENGTH;
  size = size + 1 > capacity ? size : size + 1;
}

task_state *get_next_task_state(void) {
    for (int i = 0; i < size; i++) {
      if (++current >= size) {
        current = 1;
      }
      if (tasks[current]->wait) {
        if (tasks[current]->notify) {
          tasks[current]->wait = 0;
          tasks[current]->notify = 0;
        } else {
          continue;
        }
      }
      break;
    }
  return current_task_state = tasks[current];
}

// Used in assembly code for manipulating register state structures
register_state* get_current_register_state(void) {
  return &current_task_state->registers;
}
register_state* get_next_register_state(void) {
  return &get_next_task_state()->registers;
}

void wait(void) {
  tasks[current]->wait = 1;
  while (current_task_state->wait && !current_task_state->notify) {
    cpu_hault();
  }
}

void notify(thread_t thread) { tasks[thread]->notify = 1; }

thread_t current_thread(void) { return current_task_state->id; }

message_delivery_status message_post(message_header_t header,
                                     message_payload_t payload) {
  if (header.to <= size) {
    task_state *task = tasks[header.to];
    if (task->id) {
      if (task->available_messages) {
        header.from = current_thread();
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

u16_t message_pending(void) { return current_task_state->pending_messages; }

void message_get(message_t *message) {
  // Wait until the next message is ready
  while (!message_pending()) {
    wait();
  }
  current_task_state->notify = current_task_state->wait = 0;
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
