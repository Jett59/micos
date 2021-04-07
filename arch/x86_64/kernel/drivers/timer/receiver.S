/*handles receiving timer signals and forwarding them to the main kernel*/

.code64

.text

.globl handle_timer_interrupt
handle_timer_interrupt:
pushq %rax
pushq %rbx
pushq %rcx
pushq %rdi
pushq %rdx
pushq %rsi
pushq %r8
pushq %r9
pushq %r10
pushq %r11
callq handle_timer_signal
movb $0x20, %al
outb %al, $0x20
popq %r11
popq %r10
popq %r9
popq %r8
popq %rsi
popq %rdx
popq %rdi
popq %rcx
popq %rbx
popq %rax
iretq
