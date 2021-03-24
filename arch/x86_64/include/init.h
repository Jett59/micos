#ifndef __INIT_H
#define __INIT_H  

#define INITFUNC  __attribute__ ((section (".init.text")))

#define _BOOT_LOADER_EAX_MAGIC  0x36d76289

#ifndef _ASM_FILE
int check_magic ();
void save_multiboot_info ();
#endif

#endif