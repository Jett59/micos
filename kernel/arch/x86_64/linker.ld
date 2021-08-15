ENTRY(_prestart);

SECTIONS {
    . = 1M;
    kernel_physical_start = .;
    .text :
    {
        * (.head)
        * (.init.*)
        * (.text)
    }
    .drivers :
    {
        drivers_start = .;
        * (.driver)
        drivers_end = .;
    }
    .data :
    {
        * (.data)
        * (.rodata)
        * (.rodata.*)
    }
    .bss :
    {
        _bss = .;
        * (.bss)
        * (common)
        _ebss = .;
        kernel_physical_end = .;
    }
}