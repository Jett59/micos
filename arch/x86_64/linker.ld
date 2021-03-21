SECTIONS {
    .text :
    {
        * (.head)
        * (.text)
    }
    .data :
    {
        * (.data)
        * (.rodata)
        * (.rodata.*)
    }
}