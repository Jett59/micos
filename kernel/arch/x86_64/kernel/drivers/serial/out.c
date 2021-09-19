#include <drivers/serial/serial.h>
#include <io.h>

#define COM1_BASE_ADDRESS 0x3f8
#define SERIAL_STATUS 5

static int status = 0;  // 0 = disabled, 0xFF = enabled

void set_serial_enable() { status = 0xFF; }

int is_serial_ready_for_output() {
  return inb(COM1_BASE_ADDRESS + SERIAL_STATUS) & 0x20;
}

void write_to_serial(u8_t val) {
  if (status) {
    // serial connection is enabled
    while (is_serial_ready_for_output() == 0) {
      io_delay();
    }

    outb(val, COM1_BASE_ADDRESS);
    if (val == '\n') {
      write_to_serial('\r');
    }
  }
}
