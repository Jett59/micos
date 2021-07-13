#include <stdio.h>
#include <drivers/serial/serial.h>
#include <console.h>

#define DEFAULT_CONSOLE_MODE  STDOUT

int puts (char * str)
{
    do {
        console_write_char (* str);
        write_to_serial (* str);
    }while (* (++str));
    console_write_char ('\n');
    write_to_serial ('\n');
    return 0;
}
int putchar (char c)
{
    console_write_char (c);
    write_to_serial (c);
    return (int)c;
}

static char number_table [] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

void putnum64 (u64_t num, int regex)
{
    char buffer [64];
    int count;
    do {
        buffer[count] = number_table [num % regex];
        count ++;
        num /= regex;
    }while (num);
    for (; count > 0; count --) {
        putchar (buffer [count - 1]);
    }
    putchar ('\n');
}
void puthex64 (u64_t num)
{
    putchar ('0');
    putchar ('x');
    putnum64 (num, 16);
}
