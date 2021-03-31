/*memory operations such as memset and memcpy*/

.code64

.text

.globl memset
memset:
/*rdi contains the pointer, rsi contains the value to set and rdx contains the size of the block to set*/
/*this corresponds to the c function declaration void memset (void * ptr, char c, size_t size);*/
pushq %rdi
movq %rsi, %rax
andq $0xFF, %rax /*just one byte*/
movq $0x0101010101010101, %r11
mulq %r11
pushq %rax
movq %rdx, %rax
movq $8, %rcx
div %rcx /*get the number of quads to write*/
movq %rcx, %r11 /*scratch register*/
movq %rax, %rcx
popq %rax
rep stosq
movq %r11, %rcx /*do the final bytes*/
rep stosb
popq %rax /*return the original pointer*/
retq

.globl memcpy
memcpy:
/*copy memory from rdi into rsi*/
movq %rdx, %rcx
pushq %rdi
rep movsb
popq %rax
retq
