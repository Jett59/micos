#include <interrupts.h>

void register_interrupt_handler(void (*handler)(void), u8_t intnum) {
  modify_idt(intnum, STANDARD_INTERRUPT((u64_t)handler));
}