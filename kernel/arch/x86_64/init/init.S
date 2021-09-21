.file "init.S"

.code32

.section .init.text, "ax"

.globl _start
_start:
call check_long_mode
call build_init_page_tables
call enable_pae
call set_lme_bit
call enable_paging
call load_init_gdt
jmp init_end
