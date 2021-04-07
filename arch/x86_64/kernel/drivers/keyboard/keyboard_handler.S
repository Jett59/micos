/*handles taking control and reading the key when a keyboard interrupt is fired*/

.file "keyboard_handler.S"

.code64

.text

.globl keyboard_interrupt_handler
keyboard_interrupt_handler:
pushq %rax
pushq %rbx
pushq %rcx
pushq %rdx
pushq %rsi
pushq %rdi
pushq %r8
pushq %r9
pushq %r10
pushq %r11
pushq %r12
callq key_signal
popq %r12
popq %r11
popq %r10
popq %r9
popq %r8
popq %rdi
popq %rsi
popq %rdx
popq %rcx
popq %rbx
popq %rax
iretq
