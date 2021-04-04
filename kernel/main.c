#include <stdio.h>
#include <drivers/init.h>

void arch_init (void);

void main (void)
{
    initialise_drivers ();
    console_mode (STDOUT);
    puts ("beginning kernel initialisation");
    arch_init ();
    loop:
    goto loop;
}