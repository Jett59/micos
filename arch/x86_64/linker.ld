ENTRY(_prestart);

SECTIONS {
    . = 1M;
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
}