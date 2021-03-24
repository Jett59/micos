ENTRY(_prestart);

SECTIONS {
    . = 1M;
    .text :
    {
        * (.head)
        * (.init.*)
        * (.text)
    }
    .data :
    {
        * (.data)
        * (.rodata)
        * (.rodata.*)
    }
}