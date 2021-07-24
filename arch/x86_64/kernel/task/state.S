.text

.code64

.globl save_task_state
save_task_state: /*stack parameters: task_state* state, void* rip, void* rsp*/
pushq %rbp
movq 16 (%rsp), %rbp /*Output*/
movq %rax, 16 (%rbp)
movq 24 (%rsp), %rax /*rip*/
movq %rax, (%rbp)
pushfq
popq %rax
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
