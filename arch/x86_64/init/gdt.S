/*handles basic operations to do with the global descriptor table*/

#include <gdt.h>

.code32

.section .init.text, "ax"

.globl load_init_gdt
load_init_gdt:
lgdt (gdt64_ptr)
ret

.section .init.data, "aw"

gdt64_ptr:
.word gdt64_end - gdt64 - 1
.quad gdt64
gdt64:
.quad 0 /*required null descriptor*/
.quad GDT_PRESENT(1) | GDT_LONG(1) | GDT_TYPE(1) | GDT_EXEC(1) /*64 bit segment*/
gdt64_end: