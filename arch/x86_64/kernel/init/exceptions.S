/*handles cpu exceptions during kernel initialisation*/

.code64

.text

.globl standard_init_error_no_error_code
standard_init_error_no_error_code:
pushq $0
jmp standard_init_error

.globl standard_init_error
standard_init_error:
movq $abort_message, %rdi
call puts
1:
hlt
jmp 1b

.globl standard_init_debug
standard_init_debug:
incq number_of_debug_interrupts
iretq

.data

abort_message:
.asciz "An error occured! Aborting"

.bss

.globl number_of_debug_interrupts
number_of_debug_interrupts:
.fill 8
