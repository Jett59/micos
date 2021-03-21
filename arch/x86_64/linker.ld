SECTIONS {
    .text :
    {
        * (.head)
        * (.head.text)
        * (.head.data)
        * (.text)
    }
    .data :
    {
        * (.data)
        * (.rodata)
        * (.rodata.*)
    }
}