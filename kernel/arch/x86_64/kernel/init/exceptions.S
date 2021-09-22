/*handles cpu exceptions during kernel initialisation*/

.code64

.text

.globl divide_by_zero_handler
divide_by_zero_handler:
movabsq $divide_by_zero_message, %rdi
callq fatal_error
.globl debug_handler
debug_handler:
pushq %rax
movabsq number_of_debug_interrupts, %rax
incq %rax
movabs %rax, number_of_debug_interrupts
popq %rax
iretq
.globl non_maskable_interrupt_handler
non_maskable_interrupt_handler:
movabsq $non_maskable_interrupt_message, %rdi
callq fatal_error
.globl break_point_handler
break_point_handler:
movabsq $break_point_message, %rdi
callq fatal_error
.globl overflow_handler
overflow_handler:
movabsq $overflow_message, %rdi
callq fatal_error
.globl bound_range_exceeded_handler
bound_range_exceeded_handler:
movabsq $bound_range_exceeded_message, %rdi
callq fatal_error
.globl invalid_opcode_handler
invalid_opcode_handler:
movabsq $invalid_opcode_message, %rdi
callq fatal_error
.globl device_not_available_handler
device_not_available_handler:
movabsq $device_not_available_handler, %rdi
callq fatal_error
.globl double_fault_handler
double_fault_handler:
movabsq $double_fault_message, %rdi
callq fatal_error
.globl coprocessor_exception_handler
coprocessor_exception_handler:
movabsq $coprocessor_error_message, %rdi
callq fatal_error
.globl invalid_tss_handler
invalid_tss_handler:
movabsq $invalid_tss_message, %rdi
callq fatal_error
.globl unknown_segment_handler
unknown_segment_handler:
movabsq $unknown_segment_message, %rdi
callq fatal_error
.globl stack_fault_handler
stack_fault_handler:
movabsq $stack_fault_message, %rdi
callq fatal_error
.globl general_protection_fault_handler
general_protection_fault_handler:
movabsq $general_protection_fault_message, %rdi
callq fatal_error
.globl page_fault_handler
page_fault_handler:
movabsq $page_fault_message, %rdi
callq fatal_error
.globl floating_point_exception_handler
floating_point_exception_handler:
movabsq $floating_point_message, %rdi
callq fatal_error
.globl alignment_check_handler
alignment_check_handler:
movabsq $alignment_check_message, %rdi
callq fatal_error
.globl machine_check_handler
machine_check_handler:
movabsq $machine_check_message, %rdi
callq fatal_error
.globl virtualisation_exception_handler
virtualisation_exception_handler:
movabsq $virtualisation_exception_message, %rdi
callq fatal_error
.globl security_exception_handler
security_exception_handler:
movabsq $security_exception_message, %rdi
callq fatal_error

.data

divide_by_zero_message:
.asciz "Divide by 0"
non_maskable_interrupt_message:
.asciz "Non maskable interrupt"
break_point_message:
.asciz "Unexpected break point"
overflow_message:
.asciz "Overflow detected"
bound_range_exceeded_message:
.asciz "Bound range exceeded"
invalid_opcode_message:
.asciz "Invalid opcode"
device_not_available_message:
.asciz "Device not available"
double_fault_message:
.asciz "Unknown interrupt"
coprocessor_error_message:
.asciz "Coprocessor exception"
invalid_tss_message:
.asciz "Invalid tss"
unknown_segment_message:
.asciz "Unknown segment"
stack_fault_message:
.asciz "Stack fault"
general_protection_fault_message:
.asciz "General protection fault"
page_fault_message:
.asciz "Page fault"
floating_point_message:
.asciz "Floating point exception"
alignment_check_message:
.asciz "Alignment check"
machine_check_message:
.asciz "Machine check"
virtualisation_exception_message:
.asciz "Vm error"
security_exception_message:
.asciz "Security exception"

.bss

.globl number_of_debug_interrupts
number_of_debug_interrupts:
.fill 8
