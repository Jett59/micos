TARGET=Micos
OBJECTS=head.obj

CC=clang
LD=ld.lld

AFLAGS=-target x86_64-unknown-linux-elf -fPIC -ffreestanding -I ../include
CFLAGS=-target x86_64-unknown-linux-elf -fPIC -ffreestanding -nostdlib -std=c11 -I ../include
LDFLAGS=-nostdlib -T setup.ld

all: $(TARGET)

Micos: $(OBJECTS)
	@echo "build Micos"
	@$(LD) $(LDFLAGS) $^ -o Micos.build
	@objcopy -O binary Micos.build Micos
	@rm Micos.build

%.obj: %.S
	@echo $(CC) $@
	@$(CC) $(AFLAGS) -c $^ -o $@

%.o: %.c
	@echo $(CC) $@
	@$(CC) $(CFLAGS) -c $^ -o $@