/*small driver functions*/

.code64

.text

.globl initialise_drivers
initialise_drivers:
movq $drivers_start, %rcx /*start of the driver section*/
1:
movq %rcx, %rax
cmpq $drivers_end, %rax
jae 1f
addq $10, %rcx
cmpw 8 (%rax), %di
jne 1b
pushq %rcx
pushq %rdi
callq * (%rax)
popq %rdi
popq %rcx
jmp 1b
1:
retq
