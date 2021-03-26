/*displayes error messages*/

#define ERROR_COLOR  0x04

.code32

.section .init.text, "ax"

.globl init_error
init_error: /*pointer to message stored on the stack*/
movl 4 (%esp), %esi /*error message*/
movl $0xB8000, %edi /*vga text buffer*/
1:
movb 0 (%esi), %al
cmpb $0, %al
je 1f
movb %al, 0 (%edi)
movb $ERROR_COLOR, 1 (%edi)
addl $2, %edi
incl %esi
jmp 1b
1:
hlt
jmp 1b