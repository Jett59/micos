ARCH?=x86_64

LD=ld.lld
LDFLAGS=-T arch/$(ARCH)/linker.ld

OUTDIR=arch/$(ARCH)/build
STEPS=arch/$(ARCH)/Micos.build kernel/Micos.build drivers/Micos.build fonts/Micos.build fs/Micos.build
TARGET=$(OUTDIR)/Micos

CC=clang
AS=clang

INCLUDEARGS=-I "$(CURDIR)/include" -I "$(CURDIR)/arch/$(ARCH)/include"

AFLAGS=-target $(ARCH)-unknown-none-gnu -ffreestanding $(INCLUDEARGS)
CFLAGS=-target $(ARCH)-unknown-none-gnu -ffreestanding -o2 -std=c11 $(INCLUDEARGS) -Wall -mcmodel=large
EXTERNALLDFLAGS=-relocatable

include $(CURDIR)/arch/$(ARCH)/Make.properties

all: $(TARGET)

$(TARGET): $(STEPS)
	@echo "build $(BASEDIR)/$@"
	@mkdir -p $(OUTDIR)
	@$(LD) $(LDFLAGS) $^ -o $@
	@echo "kernel file saved to $(shell pwd)/$(TARGET)"
	@rm $(STEPS)

%/Micos.build: %
	@"$(MAKE)" -s -C "$^" Micos.build BASEDIR="$(BASEDIR)/$^" ARCH="$(ARCH)" LD="$(LD)" AS="$(AS)" CC="$(CC)" AFLAGS="$(AFLAGS)" LDFLAGS="$(EXTERNALLDFLAGS)" CFLAGS="$(CFLAGS)"

clean: $(subst Micos.build,clean,$(STEPS))
	@echo "clean $(BASEDIR)/$(TARGET)"
	@rm -f $(TARGET)

%/clean: %
	@echo "clean $(BASEDIR)/$^"
	@"$(MAKE)" -s -C $^ clean BASEDIR="$(BASEDIR)/$^"
