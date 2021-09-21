/*
 *  This file sets up a stack and jumpes to the c code in init.c.
 *  The rest of booting is handled by init.c and the associated source files.
*/

#define _STACK_SIZE 512

.file "entry.S"

.code32

.section .init.text, "ax"
.globl _prestart
_prestart:
cli
cld

movl $initial_stack_top, %esp /*set up stack*/

/*perform checks and store multiboot data*/
call check_magic
cmpl $0, %eax
jne 1f
call init_error /*Reboot*/
1:
call save_multiboot_info

/*actually initialise the kernel*/
jmp _start

.section .init.data, "aw"

no_multiboot:
.asciz "Error: no multiboot2 magic number found."

.section .init.bss, "aw", @nobits

initial_stack:
.fill _STACK_SIZE
initial_stack_top:
