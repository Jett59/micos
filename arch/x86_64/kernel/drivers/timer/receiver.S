/*handles receiving timer signals and forwarding them to the main kernel*/

.code64

.text

.globl handle_timer_interrupt
handle_timer_interrupt: /*Task switch*/
pushq %rbp
movq %rsp, %rbp
pushq 24 (%rbp) /*rflags*/
pushq 32 (%rbp) /*rsp*/
pushq 8 (%rbp) /*rip*/
subq $8, %rsp

pushq %rax
pushq %rcx
pushq %rdx
pushq %rdi
pushq %rsi
pushq %r8
pushq %r9
pushq %r10
pushq %r11
callq get_current_task_state
popq %r11
popq %r10
popq %r9
popq %r8
popq %rsi
popq %rdi
popq %rdx
popq %rcx
movq %rax, -32 (%rbp)
popq %rax
movq (%rbp), %rbp
callq save_register_state

movb $0x20, %al
outb %al, $0x20
sti

callq get_next_task_state
movq %rax, %rdi
callq restore_register_state
