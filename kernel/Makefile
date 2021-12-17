LDFLAGS=-T arch/$(ARCH)/linker.ld

export CPPFLAGS:=-I "$(CURDIR)/include" -I "$(CURDIR)/arch/$(ARCH)/include"

OUTDIR=arch/$(ARCH)/build

STEPS=arch/$(ARCH)/Micos.build core/Micos.build drivers/Micos.build fonts/Micos.build fs/Micos.build exec/Micos.build
TARGET=$(OUTDIR)/Micos

CFLAGS+=-mcmodel=large -fstack-protector-strong

include arch/$(ARCH)/Make.properties

all: $(TARGET)

$(TARGET): $(STEPS)
	@echo "build $(BASEDIR)/$@"
	@mkdir -p $(OUTDIR)
	@$(LD) $(LDFLAGS) $^ -o $@
	@echo "kernel file saved to $(shell pwd)/$(TARGET)"
	@rm $(STEPS)

%/Micos.build: %
	@"$(MAKE)" -s -C "$^" Micos.build BASEDIR="$(BASEDIR)/$^" ARCH="$(ARCH)" LD="$(LD)" AS="$(AS)" CC="$(CC)" ASFLAGS="$(ASFLAGS)" LDFLAGS="" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)"

clean: $(subst Micos.build,clean,$(STEPS))
	@echo "clean $(BASEDIR)/$(TARGET)"
	@rm -f $(TARGET)

%/clean: %
	@echo "clean $(BASEDIR)/$^"
	@"$(MAKE)" -s -C $^ clean BASEDIR="$(BASEDIR)/$^"
