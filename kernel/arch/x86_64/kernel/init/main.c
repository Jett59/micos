#include <interrupts.h>
#include <pics.h>
#include <stdio.h>

extern volatile u64_t number_of_debug_interrupts;

void divide_by_zero_handler();
void debug_handler();
void non_maskable_interrupt_handler();
void break_point_handler();
void overflow_handler();
void bound_range_exceeded_handler();
void invalid_opcode_handler();
void device_not_available_handler();
void double_fault_handler();
void coprocessor_exception_handler();
void invalid_tss_handler();
void unknown_segment_handler();
void stack_fault_handler();
void general_protection_fault_handler();
void page_fault_handler();
void floating_point_exception_handler();
void alignment_check_handler();
void machine_check_handler();
void virtualisation_exception_handler();
void security_exception_handler();

static volatile idt_entry idt[256];

static volatile idt_ptr idt_pointer;

void init_interrupts() {
  idt[INTERRUPT_DIVISION] = STANDARD_INTERRUPT((u64_t)&divide_by_zero_handler);
  idt[INTERRUPT_DEBUG] = STANDARD_INTERRUPT((u64_t)&debug_handler);
  idt[INTERRUPT_NMI] =
      STANDARD_INTERRUPT((u64_t)&non_maskable_interrupt_handler);
  idt[INTERRUPT_BREAK] = STANDARD_INTERRUPT((u64_t)&break_point_handler);
  idt[INTERRUPT_OVERFLOW] = STANDARD_INTERRUPT((u64_t)&overflow_handler);
  idt[INTERRUPT_BOUND] =
      STANDARD_INTERRUPT((u64_t)&bound_range_exceeded_handler);
  idt[INTERRUPT_OPCODE] = STANDARD_INTERRUPT((u64_t)&invalid_opcode_handler);
  idt[INTERRUPT_DEVICE] =
      STANDARD_INTERRUPT((u64_t)&device_not_available_handler);
  idt[INTERRUPT_DOUBLE] = STANDARD_INTERRUPT((u64_t)&double_fault_handler);
  idt[INTERRUPT_COPROCESSOR] =
      STANDARD_INTERRUPT((u64_t)&coprocessor_exception_handler);
  idt[INTERRUPT_TSS] = STANDARD_INTERRUPT((u64_t)&invalid_tss_handler);
  idt[INTERRUPT_SEGMENT] = STANDARD_INTERRUPT((u64_t)&unknown_segment_handler);
  idt[INTERRUPT_STACK] = STANDARD_INTERRUPT((u64_t)&stack_fault_handler);
  idt[INTERRUPT_PROTECTION] =
      STANDARD_INTERRUPT((u64_t)&general_protection_fault_handler);
  idt[INTERRUPT_PAGE] = STANDARD_INTERRUPT((u64_t)&page_fault_handler);
  idt[INTERRUPT_X87] =
      STANDARD_INTERRUPT((u64_t)&floating_point_exception_handler);
  idt[INTERRUPT_ALIGNMENT] =
      STANDARD_INTERRUPT((u64_t)&alignment_check_handler);
  idt[INTERRUPT_MACHINE] = STANDARD_INTERRUPT((u64_t)&machine_check_handler);
  idt[INTERRUPT_SIMD] =
      STANDARD_INTERRUPT((u64_t)&floating_point_exception_handler);
  idt[INTERRUPT_VM] =
      STANDARD_INTERRUPT((u64_t)&virtualisation_exception_handler);
  idt[INTERRUPT_SECURITY] =
      STANDARD_INTERRUPT((u64_t)&security_exception_handler);
  idt_pointer.limit = sizeof(idt) - 1;
  idt_pointer.ptr = (u64_t)idt;
  __asm__ volatile("movabsq %0, %%rax;"
                   "lidt (%%rax);"
                   :
                   : "i"(&idt_pointer)
                   : "rax");
  u64_t preserve = number_of_debug_interrupts;
  __asm__ volatile("int %0" : : "i"(INTERRUPT_DEBUG));
  if (number_of_debug_interrupts <= preserve) {
    puts("interrupt didn't run");
  die:
    goto die;
  }
  return;
}

void scan_mbi();

void initialize_syscalls();

void arch_init() {
  scan_mbi();
  init_interrupts();
  configure_pics();
  initialize_syscalls();
  return;
}

void modify_idt(u8_t idx, idt_entry entry) { idt[idx] = entry; }
