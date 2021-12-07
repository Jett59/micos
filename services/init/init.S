.file "init.s"

.text

.globl _start
_start:
movq $0x100000000, %rcx
1: decq %rcx
jnz 1b
movq $0, %rcx
divq %rcx /*Divide by 0*/
movq (0), %rax /*Read null*/
