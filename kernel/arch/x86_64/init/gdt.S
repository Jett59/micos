/*handles basic operations to do with the global descriptor table*/

#include <gdt.h>

.file "gdt.S"

.code32

.section .init.text, "ax"

.globl load_init_gdt
load_init_gdt:
movl $gdt64_ptr, %eax
lgdt (%eax)
ret

.section .init.data, "aw"

.globl gdt64_ptr
gdt64_ptr:
.word gdt64_end - gdt64 - 1
.quad gdt64

.data

gdt64:
.quad 0 /*required null descriptor*/
.quad GDT_PRESENT(1) | GDT_LONG(1) | GDT_TYPE(1) | GDT_EXEC(1) /*64 bit segment*/
.quad 0 /*User mode code segment*/
.globl gdt_tss_descriptor
gdt_tss_descriptor:
.quad GDT_SYSTEM_TYPE(9) | GDT_PRESENT(1) /*Tss lower half*/
.quad 0 /*Tss second half*/
gdt64_end:
