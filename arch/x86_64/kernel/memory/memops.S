/*memory operations such as memset and memcpy*/

.code64

.text

.globl memset
memset:
/*rdi contains the pointer, rsi contains the value to set and rdx contains the size of the block to set*/
/*this corresponds to the c function declaration void memset (void * ptr, char c, size_t size);*/
pushq %rdi
movq %rdx, %rcx
movq %rsi, %rax
rep stosb
popq %rax
retq

.globl memcpy
memcpy:
/*copy memory from rdi into rsi*/
movq %rdx, %rcx
pushq %rdi
rep movsb
popq %rax
retq
