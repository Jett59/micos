#include <stdio.h>
#include <drivers/init.h>
#include <thread.h>
#include <error.h>
#include <time.h>
#include <memory/map.h>

#include <fs/fs.h>

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
    __asm__("sti");
    putchar('\n');
    puts("completed initialisation");
loop:
    goto loop;
}
