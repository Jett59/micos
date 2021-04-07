/*reading and writing to io ports*/

.code64

.text

.globl outb
outb: /*void outb (u8_t val, u16_t port)*/
movb %dil, %al
movw %si, %dx
outb %al, %dx
retq

.globl inb
inb: /*u8_t int (u16_t port)*/
movw %di, %dx
inb %dx, %al
retq

.globl io_delay
io_delay:
outb %al, $0x80
retq
