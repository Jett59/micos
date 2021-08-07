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
movb $10, %al
outb %al, $0x80
inb $0x71, %al
movq count, %rax
incq %rax
movq %rax, count
cmpq $1024, %rax
jb 1f
pushq %rbx
pushq %rcx
pushq %rdi
pushq %rdx
pushq %rsi
pushq %r8
pushq %r9
pushq %r10
pushq %r11
movq $msg, %rdi
callq puts
movq $0, count
popq %r11
popq %r10
popq %r9
popq %r8
popq %rsi
popq %rdx
popq %rdi
popq %rcx
popq %rbx
1:
popq %rdx
popq %rax
iretq

.data

count:
.quad 0

.rodata

msg:
.asciz "A second"
