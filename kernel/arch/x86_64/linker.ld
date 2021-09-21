ENTRY(_prestart);

SECTIONS {
    . = 1M;
    kernel_physical_start = .;
    .init :
    {
        * (.head)
        * (.init.*)
    }
    . += 0xFFFF000000000000;
    .text ALIGN (4K) : AT (ADDR (.text) - 0xFFFF000000000000)
    {
        * (.text)
    }
    .drivers ALIGN (4K) : AT (ADDR (.drivers) - 0xFFFF000000000000)
    {
        drivers_start = .;
        * (.driver)
        drivers_end = .;
    }
    .data ALIGN (4K) : AT (ADDR (.data) - 0xFFFF000000000000)
    {
        * (.data)
        * (.rodata)
        * (.rodata.*)
    }
    .bss ALIGN (4K) : AT (ADDR (.bss) - 0xFFFF000000000000)
    {
        _bss = .;
        * (.bss)
        * (common)
        _ebss = .;
        kernel_physical_end = . - 0xFFFF000000000000;
    }
}
