export ARCH?=x86_64

export LD=ld.lld
export LDFLAGS=

export CC=clang
export AS=clang

export ASFLAGS=-target $(ARCH)-unknown-none-gnu -ffreestanding
export CFLAGS=-target $(ARCH)-unknown-none-gnu -ffreestanding -O2 -std=c11 -Wall -fno-omit-frame-pointer -g

KERNEL=kernel/arch/$(ARCH)/build/Micos
SERVICES=services/init/build

all: iso

.PHONY: kernel
kernel:
	@"$(MAKE)" -C kernel -s BASEDIR=kernel
	@mkdir -p build
	@ mv $(KERNEL) build

.PHONY: services/init
services/%/build: services/%
	@"$(MAKE)" -C "$<" -s BASEDIR="$<"
	@mkdir -p build/services
	@cp -r $@/* build/services/

initramfs:
	@rm -rf build/initramfs
	@mkdir -p build/initramfs
	@cp -r init/config/* build/initramfs/
	@cp -r build/services/* build/initramfs/
	@cd build/initramfs && tar -cf ../initramfs.tar *

install:
ifeq (,$(DIR))
	@echo $(DIR)
	@echo "please provide a valid path with DIR=/path/to/install/dir"
else
	@mkdir -p $(DIR)/boot/grub
	cp build/Micos $(DIR)/boot/Micos
	@strip $(DIR)/boot/Micos
	cp build/initramfs.tar $(DIR)/boot/initramfs.tar
	cp grub/grub.cfg $(DIR)/boot/grub/grub.cfg
endif

EFI_FILE_NAME?=BOOTX64.EFI

build/efi/$(EFI_FILE_NAME):
	@mkdir -p build/efi
	@grub-mkimage -O x86_64-efi -p /boot/grub -o build/efi/$(EFI_FILE_NAME) normal part_msdos fat part_gpt all_video multiboot2

iso: kernel $(SERVICES) initramfs build/efi/$(EFI_FILE_NAME)
	@rm -rf build/grub
	@mkdir -p build/grub/boot
	@cp build/Micos build/grub/boot/Micos
	@strip build/grub/boot/Micos
	@cp build/initramfs.tar build/grub/boot/initramfs.tar
	@cp -r grub build/grub/boot/grub
	@mkdir -p build/grub/EFI/BOOT
	@cp build/efi/BOOTX64.EFI build/grub/EFI/BOOT/BOOTX64.EFI
	@grub-mkrescue -d /usr/lib/grub/i386-pc -o build/Micos.iso build/grub

clean: $(subst /build,/clean,$(SERVICES))
	@$(MAKE) -s -C kernel clean BASEDIR=kernel
	@echo "Clean build"
	@rm -rf build

%/clean: %
	@echo "clean $^"
	@"$(MAKE)" -s -C $^ clean BASEDIR="$^"

test: iso
	./debugging/qemu-test.sh
