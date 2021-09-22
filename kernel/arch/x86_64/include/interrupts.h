#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include <stdint.h>

#define INTERRUPT_DIVISION 0
#define INTERRUPT_DEBUG 1
#define INTERRUPT_NMI 2
#define INTERRUPT_BREAK 3
#define INTERRUPT_OVERFLOW 4
#define INTERRUPT_BOUND 5
#define INTERRUPT_OPCODE 6
#define INTERRUPT_DEVICE 7
#define INTERRUPT_DOUBLE 8
#define INTERRUPT_COPROCESSOR 9
#define INTERRUPT_TSS 10
#define INTERRUPT_SEGMENT 11
#define INTERRUPT_STACK 12
#define INTERRUPT_PROTECTION 13
#define INTERRUPT_PAGE 14
#define INTERRUPT_X87 16
#define INTERRUPT_ALIGNMENT 17
#define INTERRUPT_MACHINE 18
#define INTERRUPT_SIMD 19
#define INTERRUPT_VM 20
#define INTERRUPT_SECURITY 30

typedef struct __attribute__((__packed__)) {
  u16_t offset_low;
  u16_t gdt_selector;
  u8_t ist; /*interrupt stack*/
  u8_t attributes;
  u16_t offset_mid;
  u32_t offset_high;
  u32_t reserved; /*do not touch*/
} idt_entry;

typedef struct __attribute__((__packed__)) {
  u16_t limit;
  u64_t ptr;
} idt_ptr;

#define STANDARD_INTERRUPT(ADDRESS)                                           \
  (idt_entry) {                                                               \
    .offset_low = (ADDRESS)&0xFFFF,                                           \
    .offset_mid = ((ADDRESS)&0xFFFF0000) >> 16,                               \
    .offset_high = (((ADDRESS)&0xFFFFFFFF00000000ULL) >> 32ULL), .gdt_selector = 0x8, \
    .attributes = 0x8E, .ist = 0, .reserved = 0                               \
  }

void modify_idt(u8_t idx, idt_entry entry);

void register_interrupt_handler(void (*handler)(void), u8_t intnum);

#endif