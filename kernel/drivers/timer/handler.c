#include <stdio.h>

u64_t count;

void handle_timer_signal ()
{
    count++;
}