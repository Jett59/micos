.text

.globl rtc_timer_handler
rtc_timer_handler:
pushq %rax
pushq %rdx
movb $0x20, %al
movb $0x20, %dl
outb %al, %dx
movb $0xA0, %dl
outb %al, %dx
movb $0xC, %al
outb %al, $0x70
inb $0x71, %al
popq %rdx
popq %rax
iretq
