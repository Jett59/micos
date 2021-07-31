#include <stdio.h>
#include <drivers/init.h>
#include <thread.h>
#include <error.h>

void arch_init (void);

void thread_start (void* arg)
{
    char* char_arg = (char*)arg;
    for (unsigned int i = 0; ; i ++) {
        if (i % 5000000 == 0) {
            putchar (* char_arg + (i % 26));
        }
    }
}

void main (void)
{
    initialise_drivers (0);
    puts("Welcome to Micos");
    putchar ('\n');
    arch_init ();
    initialise_drivers (1);
    initialise_drivers (2);
    initialise_drivers (3);
    u32_t thread_id;
    create_thread(&thread_id, thread_start, "a");
    puts ("Thread1:");
    putnum64(thread_id, 10);
    create_thread(&thread_id, thread_start, "A");
    puts ("Thread 2:");
    putnum64(thread_id, 10);
    __asm__ ("sti");
    putchar ('\n');
    puts ("completed initialisation");    
    loop:
    goto loop;
}
