#include <interrupts.h>
#include <stdio.h>

extern u64_t number_of_init_interrupts;

void standard_init_exception ();
void standard_init_exception_no_error_code ();

static idt_entry init_idt [256];

static idt_ptr init_idt_ptr;

void init_interrupts ()
{
    init_idt [INTERRUPT_DIVISION] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_DEBUG] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_NMI] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_BREAK] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_OVERFLOW] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_BOUND] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_OPCODE] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_DEVICE] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_DOUBLE] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt [INTERRUPT_COPROCESSOR] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_TSS] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt [INTERRUPT_SEGMENT] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt [INTERRUPT_STACK] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt [INTERRUPT_PROTECTION] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt [INTERRUPT_PAGE] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt [INTERRUPT_X87] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_ALIGNMENT] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt [INTERRUPT_MACHINE] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_SIMD] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_VM] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception_no_error_code);
    init_idt [INTERRUPT_SECURITY] = STANDARD_INTERRUPT ((u64_t)&standard_init_exception);
    init_idt_ptr.limit = sizeof (init_idt) - 1;
    init_idt_ptr.ptr = &(init_idt[0]);
    __asm__ ("lidt %0" : : "m"(init_idt_ptr));
    puts ("testing division by zero");
    u64_t preserve = number_of_init_interrupts;
    __asm__ ("int %0" : : "i"(INTERRUPT_DEBUG));
    if (number_of_init_interrupts > preserve) {
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
    return;
}
