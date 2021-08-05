/*displayes error messages*/

#define ERROR_COLOR  0x04

.code32

.section .init.text, "ax"

.globl init_error
init_error:
movl $1000000, %ecx
1:
decl %ecx
jz 2f
jmp 1b
2:
int $0x1 /*tripple fault the cpu*/
