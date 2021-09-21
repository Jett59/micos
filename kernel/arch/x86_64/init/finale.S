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

/*Set the new stack*/
movabsq $stack_top, %rsp

/*Early kernel setup and main kernel code*/
movabsq $main, %rax
pushq %rax /*arch_init returns to the start of main*/
movabsq $arch_init, %rax
jmpq * %rax

.bss

stack:
.fill 65536
stack_top:
