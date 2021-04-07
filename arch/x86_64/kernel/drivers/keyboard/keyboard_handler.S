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
xorq %rax, %rax
inb $0x60, %al
movb %al, %bl
andb $0x7F, %al /*al contains scan code*/
shrb $7, %bl /*bl contains (0 for pressed, 1 for released)*/
xorb $1, %bl /*inverted now*/
leaq keymap (%rip), %rcx
addq %rcx, %rax
movb 0 (%rax), %dil

cmpb $0x1, %bl
jne 1f /*released*/

callq handle_key_pressed

1:
/*send eoi to keyboard*/
inb $0x61, %al
movb %al, %bl
orb $0x80, %al
outb %al, $0x61
movb %bl, %al
outb %al, $0x61
/*send eoi to pic*/
movb $0x20, %al
outb %al, $0x20
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

.data

keymap:
.byte 0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8
.byte 9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n'
.byte 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\n', 0
.byte 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '\\', 0, 0, 0
