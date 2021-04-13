#include <drivers/serial/serial.h>
#include <io.h>

#define COM1_IO_PORT  0x3f8
#define SERIAL_INTERRUPT_CONTROL 1
#define SERIAL_LINE_CONTROL 3
#define SERIAL_FIFO 2
#define SERIAL_INTERRUPT 4

void configure_com1 ()
{
    outb (0x80, COM1_IO_PORT + SERIAL_LINE_CONTROL); // going to set baudrate divisor
    outw (1, COM1_IO_PORT); // divisor
    outb (3, COM1_IO_PORT); // 8 bit
    outb (0xC7, COM1_IO_PORT + SERIAL_FIFO); // fifo
    outb (0x0F, COM1_IO_PORT + SERIAL_INTERRUPT); // set in normal operation mode
}