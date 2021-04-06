#include <stdio.h>
#include <drivers/init.h>

void arch_init (void);

void main (void)
{
    console_mode (STDOUT);
    puts ("beginning kernel initialization");
    putchar ('\n');
    puts ("initializing drivers");
    initialise_drivers ();
    arch_init ();
    puts ("completed initialisation");
    loop:
    goto loop;
}