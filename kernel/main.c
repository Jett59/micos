#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <drivers/init.h>

void arch_init (void);

void main (void)
{
    initialise_drivers (0);
    puts("Welcome to Micos");
    putchar ('\n');
    arch_init ();
    initialise_drivers (1);
    initialise_drivers (2);
    initialise_drivers (3);
    __asm__ ("sti");
    putchar ('\n');
    puts ("completed initialisation");
    loop:
    goto loop;
}
