#ifndef _TASK_REGISTERS_H
#define _TASK_REGISTERS_H  

#include <stdint.h>

typedef struct __attribute__ ((__packed__)) {
    u64_t rip, rflags, rax, rbp, rbx, rcx, rdi, rdx, rsi, rsp, r8, r9, r10, r11, r12, r13, r14, r15; // general-purpose
    u64_t cr3; // page table
} register_state;

#endif