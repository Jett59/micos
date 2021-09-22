.file "handler.S"

.text

.globl rtc_timer_handler
rtc_timer_handler:
pushq %rax
pushq %rdx
movb $0x20, %al
movw $0x20, %dx
 outb %al, %dx
movb $0x20, %al
movw $0xA0, %dx
outb %al, %dx
movb $0xC, %al
outb %al, $0x70
inb $0x71, %al
movabsq count, %rax
incq %rax
movabsq %rax, count
/*64 Hz*/
cmpq $16, %rax
jb 1f
popq %rdx
xorl %eax, %eax
movabsq %rax, count
popq %rax
/*Task switch*/
cli
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

callq get_next_task_state
movq %rax, %rdi
callq restore_register_state

1:
popq %rdx
popq %rax
iretq

.data

count:
.quad 0
