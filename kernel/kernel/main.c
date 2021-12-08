#include <drivers/init.h>
#include <error.h>
#include <fs/initramfs.h>
#include <memory/map.h>
#include <message.h>
#include <modules.h>
#include <paging/alloc.h>
#include <stdio.h>
#include <strings.h>
#include <thread.h>
#include <time.h>

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
    void *service_location = (void *)PAGE_SIZE;
    allocate_pages(service_location,
                   (init_service_size + PAGE_SIZE - 1) / PAGE_SIZE,
                   PAGE_WRITABLE | PAGE_USER);
    memcpy(service_location, init_service, init_service_size);
    thread_t thread_id;
    create_thread(&thread_id, (void (*)(void *))service_location, 0,
                  "Service thread 0", true);
  } else {
    fatal_error("No init service found");
  }
  wait();
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
