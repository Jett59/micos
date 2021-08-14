#include <stdio.h>
#include <drivers/init.h>
#include <thread.h>
#include <error.h>
#include <time.h>
#include <memory/map.h>

void arch_init (void);

void thread_start (void* arg)
{
    char* char_arg = (char*)arg;
    u64_t previous = 0;
    loop:
    if (previous + 1000000000 <= nanotime ()) {
        putchar (*char_arg);
        previous = nanotime ();
    }
    goto loop;
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
    thread_t thread_id;
    create_thread(&thread_id, thread_start, "a");
    puts ("Thread1:");
    putnum64(thread_id, 10);
    create_thread(&thread_id, thread_start, "A");
    puts ("Thread 2:");
    putnum64(thread_id, 10);
    puts ("Available memory:");
    u64_t available_memory = 0;
    memory_map_t* available_memory_map = get_available_memory();
    for (u32_t i = 0; i < available_memory_map->number_of_blocks; i ++) {
        available_memory += available_memory_map->blocks [i].length;
    }
    puthex64 (available_memory);
    __asm__ ("sti");
    putchar ('\n');
    puts ("completed initialisation");    
    loop:
    goto loop;
}
