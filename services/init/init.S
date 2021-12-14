.file "init.s"

.text

.globl _start
_start:
movl $0, %edi /*Post message*/
orl test_thing, %esi /*Opcode*/
shlq $16, %rsi
orl $1, %esi /*To*/
shlq $16, %rsi
xorl %edx, %edx /*Payload*/
syscall /*Post message*/
movl $2, %edi /*Get message*/
movabsq $0xFFFF800000000000, %rsi /*Kernel pointer, out of bounds*/
syscall /*Try to overwrite the kernel*/
1: jmp 1b

.bss

test_thing:
.fill 8
