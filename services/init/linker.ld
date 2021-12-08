SECTIONS {
    . = 0x1000;
    .text : {
        *(.txt)
        *(.txt.*)
    }
    .data : {
        *(.data)
        *(.data.*)
    }
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }
    .bss : {
        *(.bss)
        *(.bss.*)
        *(common)
    }
}