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
/*reload the gdt to get the high 32 bits*/
movabsq $gdt64_ptr, %rax
lgdt (%rax)

/*use the null descriptor for the data segments*/
xorl %eax, %eax
movw %ax, %ds
movw %ax, %es
movw %ax, %fs
movw %ax, %gs
movw %ax, %ss

// Set up the tss]
movabsq $gdt_tss_descriptor, %rdi
movw $104, (%rdi)
movabsq $tss, %rsi
movw %si, 2(%rdi)
movl 4(%rdi), %eax
shrq $16, %rsi
orb %sil, %al
shrq $8, %rsi
xorl %edx, %edx
movb %sil, %dl
shll $24, %edx
orl %edx, %eax
movl %eax, 4(%rdi)
shrq $8, %rsi
movl %esi, 8(%rdi)

movw $24, %ax
ltr %ax

/*Set the new stack*/
movabsq $stack_top, %rsp

/*Stack smash protector setup*/
/*Get a (random) number*/
rdtsc /*As random as possible here*/
shlq $32, %rax
orq %rdx, %rax
shrq $16, %rdx
xorq %rdx, %rax
movabsq $0xF73A92C11C29A37F, %r8
xorq %r8, %rax
movabsq %rax, __stack_chk_guard

/*Early kernel setup and main kernel code*/
movabsq $main, %rax
pushq %rax /*arch_init returns to the start of main*/
movabsq $arch_init, %rax
jmpq * %rax

.data

.globl __stack_chk_guard
__stack_chk_guard:
.quad 0 /*initialised at runtime*/

.bss

stack:
.fill 65536
stack_top:
