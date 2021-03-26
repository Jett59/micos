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

/*print 'okay'*/
movq $0x02590241024B024F, %rax /*very messy, but still*/
movq $0xB8000, %rdi
movq %rax, 0(%rdi)
1:
hlt
jmp 1b
