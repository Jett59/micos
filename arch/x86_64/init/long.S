/*helper functions for entering long mode*/

#include <EFER.h>

.code32

.section .init.text, "ax"

.globl check_long_mode
check_long_mode:
movl $0x80000000, %eax
cpuid /*highest extended feature parameter*/
cmpl $0x80000001, %eax
jb no_long_mode

movl $0x80000001, %eax
cpuid /*get extended features*/
testl $(1 << 29), %edx
jz no_long_mode
ret
no_long_mode:
call init_error /*display error message and hang*/

.globl set_lme_bit
set_lme_bit:
movl $EFER_MSR, %ecx
rdmsr
orl $EFER_LM, %eax
wrmsr /*write the long mode enable (lme) bit*/
ret
