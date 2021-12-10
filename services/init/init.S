.file "init.s"

.text

.globl _start
_start:
movl $0, %edi /*Post message*/
orl $72, %esi /*Opcode*/
shlq $16, %rsi
orl $1, %esi /*To*/
shlq $16, %rsi
xorl %edx, %edx /*Payload*/
syscall /*Post message*/
1: jmp 1b
