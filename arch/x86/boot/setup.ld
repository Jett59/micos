SECTIONS {
    .head :
    {
        . = 0; /*code is position-independent*/
        * (.head.text)
        * (.head.data)
    }
}