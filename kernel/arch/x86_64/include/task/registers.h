#ifndef _TASK_REGISTERS_H
#define _TASK_REGISTERS_H

#include <stdint.h>

#include <task/gs.h>

typedef struct __attribute__((__packed__)) {
  u64_t rip, rflags, rax, rbp, rbx, rcx, rdi, rdx, rsi, rsp, r8, r9, r10, r11,
      r12, r13, r14, r15;        // general-purpose + rip and rflags
  u64_t cr3;                     // page table
  u64_t cs, ss;                  // Code and stack segments
  u64_t active_gs, alternate_gs; // Used for swapgs
  gs_context_t gs_context;       // Data for use with syscall
} register_state;

#endif