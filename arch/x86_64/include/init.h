#ifndef __INIT_H
#define __INIT_H  

#define __CODE32  __asm__ (".code32");

#define INITFUNC  __attribute__ ((section (".init.text")))

#endif