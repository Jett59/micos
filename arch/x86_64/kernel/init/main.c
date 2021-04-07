#include <interrupts.h>
#include <pics.h>
#include <page_tables.h>
#include <stdio.h>

extern u64_t number_of_debug_interrupts;

void standard_init_error ();
void standard_init_error_no_error_code ();

void standard_init_debug ();

static idt_entry idt [256];

static idt_ptr idt_pointer;

void init_interrupts ()
{
    idt [INTERRUPT_DIVISION] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_DEBUG] = STANDARD_INTERRUPT ((u64_t)&standard_init_debug);
    idt [INTERRUPT_NMI] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_BREAK] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_OVERFLOW] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_BOUND] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_OPCODE] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_DEVICE] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_DOUBLE] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_COPROCESSOR] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_TSS] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_SEGMENT] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_STACK] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_PROTECTION] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_PAGE] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_X87] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_ALIGNMENT] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_MACHINE] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_SIMD] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt [INTERRUPT_VM] = STANDARD_INTERRUPT ((u64_t)&standard_init_error_no_error_code);
    idt [INTERRUPT_SECURITY] = STANDARD_INTERRUPT ((u64_t)&standard_init_error);
    idt_pointer.limit = sizeof (idt) - 1;
    idt_pointer.ptr = (u64_t)&(idt[0]);
    __asm__ ("lidt %0" : : "m"(idt_pointer));
    puts ("testing debug interrupt");
    u64_t preserve = number_of_debug_interrupts;
    __asm__ ("int %0" : : "i"(INTERRUPT_DEBUG));
    if (number_of_debug_interrupts > preserve) {
        puts ("Success: interrupt run");
    }else{
        puts ("interrupt didn't run");
        die:
        goto die;
    }
    return;
}

void arch_init ()
{
    puts ("initialising interrupt tables");
    init_interrupts ();
    puts ("configuring hardware interrupts");
    configure_pics ();
    init_pml4 ();
    return;
}
