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
popq %rdx
popq %rax
jb 1f
movq $0, count
1:
iretq

.data

count:
.quad 0
