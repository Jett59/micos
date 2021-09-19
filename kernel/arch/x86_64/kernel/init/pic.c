/*
 * initialization of the pic (programmable interrupt controller)
 * This is used for handling hardware irqs, such as irq 1 (keyboard event).
 */

#include <io.h>
#include <pics.h>

void reset_pics() {
  outb(0x11, 0x20); /*primary pic*/
  outb(0x11, 0xa0); /*secondary pic*/
}

void remap_pic1(u8_t base) { outb(base, 0x21); }

void remap_pic2(u8_t base) { outb(base, 0xa1); }

void enable_pics() {
  outb(2, 0xa1);
  outb(4, 0x21);
  io_delay();
  outb(1, 0x21);
  outb(1, 0xa1);
}

void configure_pics() {
  reset_pics();
  io_delay();
  remap_pic1(0x30);
  remap_pic2(0x38);
  io_delay();
  enable_pics();
}
