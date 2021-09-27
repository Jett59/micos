ARCH?=x86_64

KERNEL=kernel/arch/$(ARCH)/build/Micos

all: iso

$(KERNEL):
	@"$(MAKE)" -s -C kernel BASEDIR=kernel ARCH=$(ARCH)
	@mkdir -p build
	@ mv $(KERNEL) build

initramfs:
	@rm -rf build/initramfs/*
	@mkdir -p build/initramfs
	@cp -r init/config/* build/initramfs/
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

efiimage:
	@mkdir -p build/efi
	@grub-mkimage -O x86_64-efi -p /boot/grub -o build/efi/BOOTX64.EFI normal part_msdos fat part_gpt all_video multiboot2

iso: $(KERNEL) initramfs efiimage
	@rm -rf build/grub
	@mkdir -p build/grub/boot
	@cp build/Micos build/grub/boot/Micos
	@strip build/grub/boot/Micos
	@cp build/initramfs.tar build/grub/boot/initramfs.tar
	@cp -r grub build/grub/boot/grub
	@mkdir -p build/grub/EFI/BOOT
	@cp build/efi/BOOTX64.EFI build/grub/EFI/BOOT/BOOTX64.EFI
	@grub-mkrescue -d /usr/lib/grub/i386-pc -o build/Micos.iso build/grub

clean:
	@$(MAKE) -s -C kernel clean BASEDIR=kernel
	@echo "Clean build"
	@rm -rf build
