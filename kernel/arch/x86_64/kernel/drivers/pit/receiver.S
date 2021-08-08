/*handles receiving timer signals and forwarding them to the main kernel*/

.code64

.text

.globl handle_timer_interrupt
handle_timer_interrupt: /*Not used for now*/
pushq %rax
movb $0x20, %al
outb %al, $0x20
popq %rax
iretq
