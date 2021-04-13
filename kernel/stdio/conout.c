#include <stdio.h>

#define DEFAULT_CONSOLE_MODE  STDOUT

int puts (char * str)
{
    do {
        vga_print_char (* str, DEFAULT_CONSOLE_MODE);
    }while (* (++str));
    vga_print_char ('\n', DEFAULT_CONSOLE_MODE);
    return 0;
}
int putchar (char c)
{
    vga_print_char (c, DEFAULT_CONSOLE_MODE);
    return (int)c;
}
void putnum64 (u64_t num, int regex)
{
    char buffer [64];
    int count;
    do {
        buffer[count] = num % regex;
        count ++;
        num /= regex;
    }while (num);
    for (int i = 0; i < count; i ++) {
        putchar (buffer [count - i - 1]);
    }
    putchar ('\n');
}
void puthex64 (u64_t num)
{
    putchar ('0');
    putchar ('x');
    putnum64 (num, 16);
}
