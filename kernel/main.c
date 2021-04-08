#include <stdio.h>
#include <stdlib.h>
#include <drivers/init.h>

void arch_init (void);

void main (void)
{
    initialise_drivers (0);
    console_mode (STDOUT);
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
    puts ("testing malloc");
    int * ptr = malloc (4096);
    * ptr = 1;
    * (ptr + 1) = 0xFF;
    * (ptr + 4096) = 99;
    loop:
    goto loop;
}