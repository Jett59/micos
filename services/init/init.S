.file "init.s"

.text

.globl _start
_start:
movq $0, %rcx
divq %rcx /*Divide by 0*/
movq (0), %rax /*Read null*/
