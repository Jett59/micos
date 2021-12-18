ENTRY(_start)

SECTIONS {
    . = 0x400000;
    .text ALIGN(4k) : {
        *(.text)
        *(.text.*)
    }
    .data ALIGN(4k) : {
        *(.data)
        *(.data.*)
    }
    .rodata ALIGN(4k) : {
        *(.rodata)
        *(.rodata.*)
    }
    .init_array ALIGN(4k) : {
        __init_array_start = .;
        *(.init_array)
        __init_array_end = .;
    }
    .fini_array ALIGN(4k) : {
        __fini_array_start = .;
        *(.fini_array);
        __fini_array_end = .;
    }
    .bss ALIGN(4k) : {
        *(.bss)
        *(common)
    }
}
