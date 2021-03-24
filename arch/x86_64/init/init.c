#include <init.h>

void INITFUNC _start ()
{
    * ((int *)0xB8000) = 0x044B044F; /*OK*/
    while (1){}
}