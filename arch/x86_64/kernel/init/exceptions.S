/*handles cpu exceptions during kernel initialisation*/

.code64

.text

.globl standard_init_exception_no_error_code
standard_init_exception_no_error_code:
pushq 0
jmp standard_init_exception

.globl standard_init_exception
standard_init_exception:
pushq %rax
pushq %rbx
pushq %rcx
pushq %rdx
pushq %rdi
pushq %rsi
pushq %r8
pushq %r9
pushq %r10
pushq %r11
pushq %r12
pushq %r13
pushq %r14
pushq %r15
pushq %rbp
incq number_of_init_interrupts
call get_conmode
pushq %rax
movq $0x04, %rdi
call console_mode
movq $error_message, %rdi
call puts
popq %rdi
call console_mode
popq %rbp
popq %r15
popq %r14
popq %r13
popq %r12
popq %r11
popq %r10
popq %r9
popq %r8
popq %rsi
popq %rdi
popq %rdx
popq %rcx
popq %rbx
popq %rax
addq $8, %rsp /*error code*/
iretq

.data

error_message:
.asciz "An error occured!"

.bss

.globl number_of_init_interrupts
number_of_init_interrupts:
.fill 8
