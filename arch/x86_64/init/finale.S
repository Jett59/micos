/*exit the init code and start the main kernel*/

.code32

.section .init.text, "ax"

.globl init_end
init_end:
/*enter 64 bit mode*/
jmp $0x8, $exit_init

.code64

exit_init:
/*use the null descriptor for the data segments*/
xorq %rax, %rax
movw %ax, %ds
movw %ax, %es
movw %ax, %fs
movw %ax, %gs
movw %ax, %ss

/*reset the stack*/
movq $stack_top, %rsp
movq $stack, %rdi
movq %rsp, %rcx
subq $stack, %rcx
shrq $3, %rcx
rep stosq

callq scan_mbi

jmp main /*into the main kernel code*/
