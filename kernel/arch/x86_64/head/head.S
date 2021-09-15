/*this file contains the multiboot 2 header*/

.section .head, "a"
.align 8
header_start:
.long 0xe85250d6 /*multiboot 2 magic number*/
.long 0 /*architecture i386*/
.long header_end - header_start /*size*/
.long 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) /*checksum*/
/*tags*/

/*Information request*/
.align 8
information_request_start:
.word 1 /*type*/
.word 0 /*flags*/
.long information_request_end - information_request_start /*size*/
.long 3 /*modules*/
.long 8 /*frame buffer*/
.long 6 /*memory map*/
information_request_end:

/*Frame buffer*/
.align 8
.word 5 /*type*/
.word 0 /*flags*/
.long 20 /*size*/
.long 0 /*width, kernel doesn't mind*/
.long 0 /*height, kernel doesn't mind*/
.long 32 /*bits per pixel*/

/*Module alignment tag*/
.align 8
.word 6
.word 0
.long 8

/*end tag*/
.align 8
.word 0 /*type*/
.word 0 /*flags*/
.long 8 /*size*/
header_end:
