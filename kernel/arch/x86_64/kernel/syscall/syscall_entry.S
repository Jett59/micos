.file "syscall_entry.S"

.text

.globl syscall_entrypoint
syscall_entrypoint:
swapgs
movq %rsp, %gs:8 /*Save user mode stack*/
movq %gs:0, %rsp /*Get kernel mode stack*/
sti
pushq %rcx
pushq %r11
movq %r10, %rcx /*Move arg3 to where the compiler expects it*/
callq syscall_handler
popq %r11
popq %rcx
cli
movq %gs:8, %rsp
swapgs
sysretq
