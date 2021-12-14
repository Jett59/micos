#include <drivers/init.h>
#include <error.h>
#include <exec.h>
#include <fs/initramfs.h>
#include <message.h>
#include <modules.h>
#include <paging/alloc.h>
#include <stdio.h>
#include <strings.h>
#include <thread.h>

void thread_start(void *arg) {
  // Find the init.conf file
  boot_module_t *module;
  const unsigned char *init_conf = 0;
  size_t init_conf_size = 0;
  for (int i = 0; (module = get_boot_module(i)); i++) {
    init_conf_size =
        initramfs_read(module->start, module->size, "init.conf", &init_conf);
    if (init_conf_size) {
      break;
    }
  }
  if (init_conf) {
    puts("Found init.conf:");
    for (size_t i = 0; i < init_conf_size; i++) {
      putchar((char)(init_conf[i]));
    }
    putchar('\n');
  }
  puts("Done!");
  // Find the init service binary
  const unsigned char *init_service;
  size_t init_service_size = 0;
  for (int i = 0; (module = get_boot_module(i)); i++) {
    init_service_size =
        initramfs_read(module->start, module->size, "init", &init_service);
    if (init_service_size != 0) {
      break;
    }
  }
  if (init_service_size != 0) {
    puts("Found init service binary");
    exec_entrypoint init_service_entrypoint;
    if (exec_load(init_service, init_service_size, &init_service_entrypoint) == EXEC_SUCCESS) {
    thread_t thread_id;
    create_thread(&thread_id, (void (*)(void *))init_service_entrypoint, 0,
                  "Service thread 0", true);
    }else {
      fatal_error("Init service not a valid executable");
    }
  } else {
    fatal_error("No init service found");
  }
  while (true) {
    message_t message;
    message_get(&message);
    puts("Got message with opcode:");
    putdec64(message.header.opcode);
    puts("From thread:");
    putdec64(message.header.from);
  }
}

void main(void) {
  initialise_drivers(0);
  puts("Welcome to Micos");
  putchar('\n');
  initialise_drivers(1);
  initialise_drivers(2);
  initialise_drivers(3);
  thread_t thread_id;
  create_thread(&thread_id, thread_start, "a", "Initial kernel thread", false);
  __asm__("sti");
  putchar('\n');
  puts("completed initialisation");
  while (1)
    ;
}
