.file "crt0.s"

#define STACK_SIZE  65536

.text

.globl _start
_start:
leaq STACK_SIZE + stack(%rip), %rsp
jmp _init

.bss

stack:
.fill STACK_SIZE
