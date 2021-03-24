/*
 *  This file sets up a stack and jumpes to the c code in init.c.
 *  The rest of booting is handled by init.c and the associated source files.
*/

#define __STACK_SIZE 65536

.code32

.section .init.text, "ax"
.globl _prestart
_prestart:
cli
cld

movl $stack, %esp /*set up stack*/
addl $__STACK_SIZE, %esp /*point at the end of the stack as stack grows downwards*/

/*push all modified registers (initialisation is quite dangerous)*/
pushl %edi
pushl %ecx
pushl %eax

/*clear video ram*/
movl $0xB8000, %edi
movl $2000, %ecx
xorl %eax, %eax
rep stosl

/*restore original state*/
popl %eax
popl %ecx
popl %edi

/*perform checks and store multiboot data*/
call check_magic
cmpl $0, %eax
je error
call save_multiboot_info

/*actually start the kernel*/
jmp _start

error:
movl $0xB8000, %edi
movl $2000, %ecx
movl $0x40144014, %eax /*red space*/
rep stosl
1:
hlt
jmp 1b

.lcomm stack, __STACK_SIZE
.lcomm empty_idt, 6