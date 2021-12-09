.file "syscall_entry.S"

.text

.globl syscall_entrypoint
syscall_entrypoint:
sti
sysretq
