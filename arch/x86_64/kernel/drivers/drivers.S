/*small driver functions*/

.code64

.text

.globl initialise_drivers
initialise_drivers:
movq $drivers_start, %rax /*start of the driver section*/
1:
cmpq $drivers_end, %rax
jae 1f
pushq %rax
callq * (%rax)
popq %rax
addq $8, %rax
jmp 1b
1:
retq
