.text

.code64

.globl save_register_state
save_register_state: /*stack parameters: register_state* state, void* rip, void* rsp, u64_t rflags, u64_t ss, u64_t cs*/
pushq %rbp
movq 16 (%rsp), %rbp /*Output*/
cmpq $0x0, %rbp
jne 1f
popq %rbp
retq
1:
movq %rax, 16 (%rbp)
movq 24 (%rsp), %rax /*rip*/
movq %rax, (%rbp)
movq 40 (%rsp), %rax
movq %rax, 8 (%rbp) /*rflags*/
popq %rax
movq %rax, 24 (%rbp) /*rbp*/
movq %rbx, 32 (%rbp) /*rbx*/
movq %rcx, 40 (%rbp) /*rcx*/
movq %rdi, 48 (%rbp) /*rdi*/
movq %rdx, 56 (%rbp) /*rdx*/
movq %rsi, 64 (%rbp) /*rsi*/
movq 24 (%rsp), %rax
movq %rax, 72 (%rbp) /*rsp*/
movq %r8, 80 (%rbp) /*r8*/
movq %r9, 88 (%rbp) /*r9*/
movq %r10, 96 (%rbp) /*r10*/
movq %r11, 104 (%rbp) /*r11*/
movq %r12, 112 (%rbp) /*r12*/
movq %r13, 120 (%rbp) /*r13*/
movq %r14, 128 (%rbp) /*r14*/
movq %r15, 136 (%rbp) /*r15*/
movq %cr3, %rax
movq %rax, 144 (%rbp) /*cr3*/
movq 40(%rsp), %rax
movq %rax, 160(%rbp) /*ss*/
movq 48(%rsp), %rax
movq %rax, 152(%rbp) /*cs*/

movq $32, %rdx
movl $0xC0000101, %ecx /*Active gs base*/
rdmsr /*Get it*/
shlq $32, %rdx
orq %rax, %rdx
movq %rdx, 168(%rbp) /*Active gs base*/

movl $0xC0000102, %ecx /*Alternate gs base*/
rdmsr /*Get it*/
shlq $32, %rdx
orq %rax, %rdx
movq %rdx, 176(%rbp) /*Alternate gs base*/
retq

.globl restore_register_state
restore_register_state: /*Register parameter rdi: register_state* state*/
movq %rdi, %rbp

movabsq $tss, %rdi
movq 184(%rbp), %rdx
movq %rdx, 4(%rdi) /*Put the kernel stack in the tss for the cpu*/

movq 168(%rbp), %rdi
movl %edi, %eax
shrq $32, %rdi
movl %edi, %edx
movl $0xC0000101, %ecx /*Active gs base*/
wrmsr /*Set active gs base*/
movq 176(%rbp), %rdi
movl %edi, %eax
shrq $32, %rdi
movl %edi, %edx
movl $0xC0000102, %ecx /*Alternate gs base*/
wrmsr /*Set alternate gs base for syscall*/
pushq 160(%rbp) /*ss*/
pushq 72 (%rbp) /*rsp*/
pushq 8 (%rbp) /*rflags*/
pushq 152(%rbp) /*cs*/
pushq (%rbp) /*rip*/
movq 16 (%rbp), %rax /*rax*/
pushq 24 (%rbp) /*rbp*/
movq 32 (%rbp), %rbx /*rbx*/
movq 40 (%rbp), %rcx /*rcx*/
movq 48 (%rbp), %rdi /*rdi*/
movq 56 (%rbp), %rdx /*rdx*/
movq 64 (%rbp), %rsi /*rsi*/
movq 80 (%rbp), %r8 /*r8*/
movq 88 (%rbp), %r9 /*r9*/
movq 96 (%rbp), %r10 /*r10*/
movq 104 (%rbp), %r11 /*r11*/
movq 112 (%rbp), %r12 /*r12*/
movq 120 (%rbp), %r13 /*r13*/
movq 128 (%rbp), %r14 /*r14*/
movq 136 (%rbp), %r15 /*r15*/
pushq %rax
movq 144 (%rbp), %rax
movq %rax, %cr3 /*page table*/
popq %rax
popq %rbp
iretq /*set ss, rsp, rflags, cs and rip*/
