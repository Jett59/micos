#include <asm/head.h>

.code32

__HEADTEXT

__magic:
.byte 0xB8,0xFE,0x4C,0xCD,0x21

jmp _start

.globl _start
_start:
1:
hlt
jmp 1b