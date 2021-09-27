#include <drivers/init.h>
#include <error.h>
#include <fs/initramfs.h>
#include <memory/map.h>
#include <modules.h>
#include <stdio.h>
#include <thread.h>
#include <time.h>

void thread_start(void *arg) {
  // Find the init.conf file
  boot_module_t *module;
  const char *init_conf = 0;
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
      putchar(init_conf[i]);
    }
    putchar('\n');
  }
loop:
  goto loop;
}

void main(void) {
  initialise_drivers(0);
  puts("Welcome to Micos");
  putchar('\n');
  initialise_drivers(1);
  initialise_drivers(2);
  initialise_drivers(3);
  thread_t thread_id;
  create_thread(&thread_id, thread_start, "a", "Initial kernel thread");
  __asm__("sti");
  putchar('\n');
  puts("completed initialisation");
loop:
  goto loop;
}
