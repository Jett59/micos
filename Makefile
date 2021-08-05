ARCH?=x86_64

KERNEL=kernel/arch/$(ARCH)/build/Micos

all: $(KERNEL)

$(KERNEL):
	@$(MAKE) -s -C kernel BASEDIR=kernel ARCH=$(ARCH)
	@mkdir -p build
	@ mv $(KERNEL) build

clean:
	@$(MAKE) -s -C kernel clean BASEDIR=kernel
