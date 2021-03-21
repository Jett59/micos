ARCH=x86_64

LD=ld.lld
LDFLAGS=-T arch/$(ARCH)/linker.ld

OUTDIR=arch/$(ARCH)/build
STEPS=arch/$(ARCH)/Micos.build
TARGET=$(OUTDIR)/Micos

CC=clang
AS=clang

AFLAGS=-target $(ARCH)-unknown-linux-elf -ffreestanding
CFLAGS=-target $(ARCH)-unknown-linux-elf -ffreestanding -std=c11
EXTERNALLDFLAGS=-relocatable

all: $(TARGET)

$(TARGET): $(STEPS)
	@echo "build $@"
	@mkdir -p $(OUTDIR)
	@$(LD) $(LDFLAGS) $^ -o $@
	@echo "kernel file saved to $(shell pwd)/$(TARGET)"

%/Micos.build: %
	@$(MAKE) -s -C "$^" Micos.build BASEDIR="$^" ARCH="$(ARCH)" LD="$(LD)" AS="$(AS)" CC="$(CC)" AFLAGS="$(AFLAGS)" LDFLAGS="$(EXTERNALLDFLAGS)"

clean: $(subst Micos.build,clean,$(STEPS))
	$(info clean build output)
	@rm $(STEPS)
	$(info clean $(TARGET))
	@rm $(TARGET)

%/clean: %
	@echo "clean $^"
	@$(MAKE) -s -C $^ clean BASEDIR="$@"
