#include <console.h>
#include <drivers/serial/serial.h>
#include <lock.h>
#include <stdio.h>

#define DEFAULT_CONSOLE_MODE STDOUT

static lock_t console_lock;

int puts(char *str) {
  synchronise(&console_lock);
  do {
    console_write_char(*str);
    write_to_serial(*str);
  } while (*(++str));
  console_write_char('\n');
  write_to_serial('\n');
  free_lock(&console_lock);
  return 0;
}
int putchar(char c) {
  synchronise(&console_lock);
  console_write_char(c);
  write_to_serial(c);
  free_lock(&console_lock);
  return (int)c;
}

static char number_table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                              '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void putnum64(u64_t num, int radix) {
  char buffer[64];
  int count = 0;
  do {
    buffer[count] = number_table[num % radix];
    count++;
    num /= radix;
  } while (num && count < 64);
  synchronise(&console_lock);
  for (; count-- > 0;) {
    console_write_char(buffer[count]);
    write_to_serial(buffer[count]);
  }
  console_write_char('\n');
  write_to_serial('\n');
  free_lock(&console_lock);
}
