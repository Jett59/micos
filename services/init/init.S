.file "init.s"

.text

.globl _start
_start:
movq $101, %rdi
syscall /*Debug trace*/
1: jmp 1b
