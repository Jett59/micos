/*useful functions for such things as converting integers to pointers*/

.code64

.text

.globl to_pointer
to_pointer:
movq %rdi, %rax
retq
