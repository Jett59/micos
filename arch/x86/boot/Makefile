TARGET=Micos
OBJECTS=head.obj

AFLAGS=-ffreestanding -I ../include
CFLAGS=-ffreestanding -nostdlib -std=c11 -I ../include
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