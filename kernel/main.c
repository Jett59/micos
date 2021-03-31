#include <stdio.h>
#include <drivers/init.h>

void main (void)
{
    initialise_drivers ();
    console_mode (STDOUT);
    puts ("Hello, World!");
    loop:
    goto loop;
}