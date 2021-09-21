/*for dealing with page tables*/

#include <paging.h>

.code32

.section .init.text, "ax"

.globl build_init_page_tables
build_init_page_tables:
movl $level_3, %eax
orl $3, %eax /*present + writable*/
movl %eax, level_4

movl $level_2, %eax
orl $3, %eax /*present + writable*/
movl %eax, level_3

/*set up the huge page tables*/
pushl %edi
movl $512, %ecx /*2 mb pages*/
movl $level_2, %edi
movl $0x83, %eax
1: movl %eax, 0 (%edi)
addl $0x200000, %eax
addl $8, %edi
decl %ecx
jnz 1b

/*put the address into cr3*/
movl $level_4, %eax
movl %eax, %cr3

popl %edi
ret

.globl enable_pae
enable_pae:
movl %cr4, %eax
orl $CR4_PAE, %eax
movl %eax, %cr4 /*pae enabled*/
ret

.globl enable_paging
enable_paging:
movl %cr0, %eax
orl $CR0_PAGING, %eax
movl %eax, %cr0
ret

.section .init.bss, "aw", @nobits

.align 4096
level_4:
.fill 4096
level_3:
.fill 4096
level_2:
.fill 4096
