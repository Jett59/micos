/*
 *  This file manages the configuration from the multiboot compliant boot loader.
*/

#define _ASM_FILE  1
#include <init.h>

.file "multiboot.S"

.code32

.section .init.text, "ax"

.globl check_magic
check_magic:
cmpl $_BOOT_LOADER_EAX_MAGIC, %eax
jne 1f
movl $1, %eax
jmp 2f
1:
movl $0, %eax
2:
ret

.globl save_multiboot_info
save_multiboot_info:
movl $multiboot_data_ptr, %ecx
movl %ebx, 0 (%ecx)
ret

.section .init.data, "aw"
.globl multiboot_data_ptr
multiboot_data_ptr:
.quad 0 /*pointer to multiboot information structure*/
