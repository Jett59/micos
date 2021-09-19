#include <drivers/init.h>
#include <interrupts.h>
#include <io.h>

void handle_timer_interrupt(void);

void timer_init(void);

static DRIVER timer_driver = {.init = timer_init, .priority = 1};

void timer_init(void) {
  register_interrupt_handler(handle_timer_interrupt, 0x30);

  // Set up the pic chip
  // Channel 0, access both bytes, square wave mode, binary mode
  outb((0 << 6) | (3 << 4) | (3 << 1) | (0 << 0), 0x43);
  // Frequency divisor: 1024
  // Low byte: 0
  outb(0, 0x40);
  // High byte: 4
  outb(4, 0x40);
  timer_driver.init = 0;
}
