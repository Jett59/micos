/*small driver functions*/

.code64

.text

.globl initialise_drivers
initialise_drivers:
movabsq $drivers_start, %rcx /*start of the driver section*/
movabsq $drivers_end, %rdx
1:
movq %rcx, %rax
cmpq %rdx, %rax
jae 1f
addq $10, %rcx
cmpw 8 (%rax), %di
jne 1b
pushq %rcx
pushq %rdi
pushq %rdx
callq * (%rax)
popq %rdx
popq %rdi
popq %rcx
jmp 1b
1:
retq
