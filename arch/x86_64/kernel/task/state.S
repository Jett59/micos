.text

.code64

.globl save_register_state
save_register_state: /*stack parameters: register_state* state, void* rip, void* rsp, u64_t rflags*/
pushq %rbp
movq 16 (%rsp), %rbp /*Output*/
movq %rax, 16 (%rbp)
movq 24 (%rsp), %rax /*rip*/
movq %rax, (%rbp)
movq 40 (%rsp), %rax
movq %rax, 8 (%rbp) /*rflags*/

movq %rbx, 24 (%rbp) /*rbx*/
popq %rax
movq %rax, 32 (%rbp) /*rbp*/
movq %rcx, 40 (%rbp) /*rcx*/
movq %rdi, 48 (%rbp) /*rdi*/
movq %rdx, 56 (%rbp) /*rdx*/
movq %rsi, 64 (%rbp) /*rsi*/
movq 32 (%rsp), %rax
movq %rax, 72 (%rbp) /*rsp*/
movq %r8, 80 (%rbp) /*r8*/
movq %r9, 88 (%rbp) /*r9*/
movq %r10, 96 (%rbp) /*r10*/
movq %r11, 104 (%rbp) /*r11*/
movq %r12, 112 (%rbp) /*r12*/
movq %r13, 120 (%rbp) /*r13*/
movq %r14, 128 (%rbp) /*r14*/
movq %r15, 136 (%rbp) /*r15*/
movq %cr4, %rax
movq %rax, 144 (%rbp) /*cr4*/
retq
.globl restore_register_state
restore_register_state: /*Register parameter rdi: register_state* state*/
movq %rdi, %rbp
pushq $0 /*ss*/
pushq 72 (%rbp) /*rsp*/
pushq 8 (%rbp) /*rflags*/
pushq $8 /*cs*/
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
