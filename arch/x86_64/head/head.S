/*
*  Prepare for entering the kernel.
*  This consists mainly of entering long mode.
*/

.code32
.intel_syntax

.section .head, "a"
header_start:
.long 0xe85250d6 /*multiboot 2 magic number*/
.long 0 /*architecture i386*/
.long header_end - header_start /*size*/
.long 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) /*checksum*/
/*tags*/

/*end tag*/
.word 0 /*type*/
.word 0 /*flags*/
.long 8 /*size*/
header_end:
