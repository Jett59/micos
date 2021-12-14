ARCH?=x86_64

CC:=clang
AS:=clang

TARGET:=$(ARCH)-unknown-none-gnu

CFLAGS:=-target $(TARGET) -ffreestanding
AFLAGS:=-target $(TARGET) -ffreestanding

LD:=ld.lld
LDFLAGS:=-T linker.ld

STEPS:=init.o

build/init: $(STEPS)
	mkdir -p build
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.S
	echo "$(AS) $(BASEDIR)/$@"
	$(AS) $(AFLAGS) -c $^ -o $@

clean:
	rm -f $(STEPS)
	rm -rf build
