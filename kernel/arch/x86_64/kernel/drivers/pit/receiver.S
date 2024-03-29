/*handles receiving timer signals and forwarding them to the main kernel*/

.code64

.text

.globl handle_timer_interrupt
handle_timer_interrupt: /*Not used for now*/
pushq %rax
movabsq current_time_nanos, %rax
addq $858210, %rax /*tick duration*/
movabsq %rax, current_time_nanos
movb $0x20, %al
outb %al, $0x20
popq %rax
iretq

.globl nanotime
nanotime:
movabsq current_time_nanos, %rax
retq

.data

current_time_nanos:
.quad 0
