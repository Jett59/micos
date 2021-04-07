#include <stdio.h>

void handle_key_pressed (char key)
{
    conmode_t old_conmode = get_conmode ();
    console_mode (STDIN);
    putchar (key);
    console_mode (old_conmode);
}