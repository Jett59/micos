/*handles receiving timer signals and forwarding them to the main kernel*/

.code64

.text

.globl handle_timer_interrupt
handle_timer_interrupt: /*Not used for now*/
pushq %rax
movb $0x20, %al
outb %al, $0x20
movq current_time_nanos, %rax
addq $53638, %rax /*tick duration*/
movq %rax, current_time_nanos
popq %rax
iretq

.globl nanotime
nanotime:
movq current_time_nanos, %rax
retq

.data

current_time_nanos:
.quad 0
