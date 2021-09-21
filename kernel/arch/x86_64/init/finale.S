/*exit the init code and start the main kernel*/

.file "finale.S"

.code32

.section .init.text, "ax"

.globl init_end
init_end:
/*enter 64 bit mode*/
jmp $0x8, $exit_init

.code64

exit_init:
/*use the null descriptor for the data segments*/
xorl %eax, %eax
movw %ax, %ds
movw %ax, %es
movw %ax, %fs
movw %ax, %gs
movw %ax, %ss

/*reset the stack*/
movabsq $stack_top, %rsp
movabsq $stack, %rdi
movq %rsp, %rcx
subq %rdi, %rcx
shrq $3, %rcx
rep stosq

/*Early kernel setup*/
movabsq $arch_init, %rax
callq * %rax

movabsq $main, %rax
jmp * %rax /*into the main kernel code*/

.bss

stack:
.fill 65536
stack_top:
