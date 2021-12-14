SECTIONS {
    . = 0x20000;
    .text ALIGN(4k) : {
        *(.txt)
        *(.txt.*)
    }
    .data ALIGN(4k) : {
        *(.data)
        *(.data.*)
    }
    .rodata ALIGN(4k) : {
        *(.rodata)
        *(.rodata.*)
    }
    .bss ALIGN(4k) : {
        *(.bss)
        *(.bss.*)
        *(common)
    }
}