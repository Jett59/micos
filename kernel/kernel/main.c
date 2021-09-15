#include <stdio.h>
#include <drivers/init.h>
#include <thread.h>
#include <error.h>
#include <time.h>
#include <memory/map.h>

#include <modules.h>

void thread_start(void *arg)
{
loop:
    goto loop;
}

void main(void)
{
    initialise_drivers(0);
    puts("Welcome to Micos");
    putchar('\n');
    initialise_drivers(1);
    initialise_drivers(2);
    initialise_drivers(3);
    thread_t thread_id;
    create_thread(&thread_id, thread_start, "a", "Initial kernel thread");
    puts("Primary module:");
    boot_module_t *boot_module = get_boot_module(0);
    puts(boot_module->name);
    for (size_t i = 0; i < boot_module->size; i ++) {
        putchar(((char*)boot_module->start)[i]);
    }
    __asm__("sti");
    putchar('\n');
    puts("completed initialisation");
loop:
    goto loop;
}
