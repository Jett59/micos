ARCH=x86_64

LD=ld.lld
LDFLAGS=-T arch/$(ARCH)/linker.ld

OUTDIR=arch/$(ARCH)/build
STEPS=arch/$(ARCH)/Micos.build
TARGET=$(OUTDIR)/Micos

CC=clang
AS=clang

INCLUDEARGS=-I "$(CURDIR)/include" -I "$(CURDIR)/arch/$(ARCH)/include"

AFLAGS=-target $(ARCH)-unknown-linux-elf -ffreestanding $(INCLUDEARGS)
CFLAGS=-target $(ARCH)-unknown-linux-elf -ffreestanding -std=c11 $(INCLUDEARGS)
EXTERNALLDFLAGS=-relocatable

all: $(TARGET)

$(TARGET): $(STEPS)
	@echo "build $@"
	@mkdir -p $(OUTDIR)
	@$(LD) $(LDFLAGS) $^ -o $@
	@echo "kernel file saved to $(shell pwd)/$(TARGET)"

%/Micos.build: %
	@$(MAKE) -s -C "$^" Micos.build BASEDIR="$^" ARCH="$(ARCH)" LD="$(LD)" AS="$(AS)" CC="$(CC)" AFLAGS="$(AFLAGS)" LDFLAGS="$(EXTERNALLDFLAGS)" CFLAGS="$(CFLAGS)"

clean: $(subst Micos.build,clean,$(STEPS))
	@echo "clean build output"
	@rm $(STEPS)
	@echo "clean $(TARGET)"
	@rm $(TARGET)

%/clean: %
	@echo "clean $^"
	@$(MAKE) -s -C $^ clean BASEDIR="$@"
