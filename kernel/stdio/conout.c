#include <stdio.h>
#include <drivers/serial/serial.h>

#define DEFAULT_CONSOLE_MODE  STDOUT

int puts (char * str)
{
    do {
        vga_print_char (* str, DEFAULT_CONSOLE_MODE);
        write_to_serial (* str);
    }while (* (++str));
    vga_print_char ('\n', DEFAULT_CONSOLE_MODE);
    write_to_serial ('\n');
    return 0;
}
int putchar (char c)
{
    vga_print_char (c, DEFAULT_CONSOLE_MODE);
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
