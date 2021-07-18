#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <drivers/init.h>

void arch_init (void);

void main (void)
{
    initialise_drivers (0);
    puts ("initialising");
    putchar ('\n');
    arch_init ();
    puts ("initialising drivers");
    initialise_drivers (1);
    initialise_drivers (2);
    initialise_drivers (3);
    puts ("enabling hardware interrupts");
    __asm__ ("sti");
    putchar ('\n');
    puts ("completed initialisation");
    puts("Testing uncached malloc");
    int* ptr = malloc_uncacheable(7*sizeof(int));
    *ptr = 99;
    putnum64(*ptr, 10);
    free(ptr);
    loop:
    goto loop;
}
