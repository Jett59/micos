/*memory operations such as memset and memcpy*/

.code64

.text

.globl memset
memset:
/*rdi contains the pointer, rsi contains the value to set and rdx contains the size of the block to set*/
/*this corresponds to the c function declaration void memset (void * ptr, char c, size_t size);*/
pushq %rdi
xorl %eax, %eax
movb %sil, %al
movabsq $0x0101010101010101, %rcx
movq %rdx, %r11
mulq %rcx
movq %r11, %rcx
andq $7, %r11 /*remainder of division by 8*/
shrq $3, %rcx /*divided by eight*/
rep stosq /*store the quad words*/
movq %r11, %rcx
rep stosb /*and the rest*/
popq %rax
retq

.globl memcpy
memcpy:
/*copy memory from rsi into rdi*/
pushq %rdi
movq %rdx, %rcx
andq $7, %rdx /*remainder of division by 8*/
shrq $3, %rcx /*divided by eight*/
rep movsq /*store the quad words*/
movq %rdx, %rcx
rep movsb /*and the rest*/
popq %rax
retq
