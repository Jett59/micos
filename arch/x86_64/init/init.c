#include <init.h>
#include <init/init.h>
#include <init/longmode.h>
#include <init/paging.h>
#include <init/gdt.h>

void INITFUNC _start ()
{
    check_long_mode ();
    build_init_page_tables ();
    enable_pae ();
    set_lme_bit ();
    enable_paging ();
    load_init_gdt ();
    init_end ();
}