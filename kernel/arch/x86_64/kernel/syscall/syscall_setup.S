.file "syscall_setup.S"

.text

.globl initialize_syscalls
initialize_syscalls:
pushq %rbp
movq %rsp, %rbp
movl $0xC0000080, %ecx /*EFER*/
rdmsr
orl $1, %eax
wrmsr /*Enable syscall instructions*/
xorl %edx, %edx
orl $32, %edx /*User mode selectors*/
shll $16, %edx
orl $8, %edx /*Kernel mode selectors*/
xorl %eax, %eax
movl $0xC0000081, %ecx /*STAR*/
wrmsr /*Set sysret and syscall segment selectors*/
movabsq $syscall_entrypoint, %rdi
movl %edi, %eax /*Low 32 bits of entrypoint*/
shrq $32, %rdi
movl %edi, %edx /*High 32 bits of entrypoint*/
movl $0xC0000082, %ecx /*LSTAR*/
wrmsr
xorl %eax, %eax
orl $(1 << 9), %eax /*Mask interrupts*/
movl $0xC0000084, %ecx /*SFMASK*/
wrmsr
popq %rbp
retq
