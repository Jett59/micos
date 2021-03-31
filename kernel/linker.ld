sections {
    .text : 
    {
        * (.text)
    }
    .driver :
    {
        * (.driver)
    }
    .rodata :
    {
        * (.rodata)
        * (.rodata.*)
    }
    .data :
    {
        * (.data)
    }
    .bss :
    {
        * (.bss)
    }
}