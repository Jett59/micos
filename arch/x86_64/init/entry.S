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

movl $stack_top, %esp /*set up stack*/

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
jne 1f
pushl $no_multiboot
call init_error /*print error message and hang forever*/
1:
call save_multiboot_info

/*actually initialise the kernel*/
jmp _start

.section .init.data, "aw"

no_multiboot:
.asciz "Error: no multiboot2 magic number found."

.bss

.globl stack
.globl stack_top

stack:
.fill __STACK_SIZE
stack_top:
