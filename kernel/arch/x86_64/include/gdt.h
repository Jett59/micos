#ifndef _GDT_H
#define _GDT_H

#define GDT_SYSTEM_TYPE(X) ((X & 0xF) << 40)
#define GDT_CONFORMING(X) ((X & 1) << 42)
#define GDT_EXEC(X) ((X & 1) << 43)
#define GDT_TYPE(X) ((X & 1) << 44)
#define GDT_PRIV(X) ((X & 3) << 45)
#define GDT_PRESENT(X) ((X & 1) << 47)
#define GDT_LONG(X) ((X & 1) << 53)
#define GDT_SIZE(X) ((X & 1) << 54)

#endif