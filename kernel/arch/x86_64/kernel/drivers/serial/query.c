#include <drivers/serial/serial.h>
#include <io.h>

#define COM1_BASE_REGISTER 0x3f8
#define SERIAL_LINE_CONTROL 3
#define SERIAL_SCRATCH_OFFSET 7

int query_com1() {
  u8_t orig_scratch = inb(COM1_BASE_REGISTER + SERIAL_SCRATCH_OFFSET);
  u8_t new_scratch = orig_scratch ^ 0xEE;
  // is the scratch register writable?
  outb(new_scratch, COM1_BASE_REGISTER + SERIAL_SCRATCH_OFFSET);
  io_delay();
  if (inb(COM1_BASE_REGISTER + SERIAL_SCRATCH_OFFSET) ^ orig_scratch) {
    outb(orig_scratch, COM1_BASE_REGISTER + SERIAL_SCRATCH_OFFSET);
    u8_t orig_line_control = inb(COM1_BASE_REGISTER + SERIAL_LINE_CONTROL);
    u8_t new_line_control = orig_line_control ^ 0x80;  // flip the DLAB bit
    u16_t orig_divisor_register = inw(COM1_BASE_REGISTER);
    // does flipping the DLAB change the value of the divisor register?
    outb(new_line_control, COM1_BASE_REGISTER + SERIAL_LINE_CONTROL);
    if (inw(COM1_BASE_REGISTER) ^ orig_divisor_register) {
      outb(orig_line_control, COM1_BASE_REGISTER + SERIAL_LINE_CONTROL);
      return 1;  // probably does exist
    }
  }
  return 0;  // no com port
}
