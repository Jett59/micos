ARCH?=x86_64

KERNEL=kernel/arch/$(ARCH)/build/Micos

all: $(KERNEL)

$(KERNEL):
	@"$(MAKE)" -s -C kernel BASEDIR=kernel ARCH=$(ARCH)
	@mkdir -p build
	@ mv $(KERNEL) build

install:
ifeq (,$(DIR))
	@echo $(DIR)
	@echo "please provide a valid path with DIR=/path/to/install/dir"
else
	@mkdir -p $(DIR)/boot
	@rm -f $(DIR)/boot/Micos
	cp build/Micos $(DIR)/boot/Micos
endif

efiimage:
	@mkdir -p build/efi
	@grub-mkimage -O x86_64-efi -p /boot/grub -o build/efi/BOOTX64.EFI part_msdos fat part_gpt all_video multiboot2

iso: $(KERNEL) efiimage
	@rm -rf build/boot
	@mkdir -p build/grub/boot
	@cp build/Micos build/grub/boot/Micos
	@strip build/grub/boot/Micos
	@cp -r grub build/grub/boot/grub
	@mkdir -p build/grub/EFI/BOOT
	@cp build/efi/BOOTX64.EFI build/grub/EFI/BOOT/BOOTX64.EFI
	@grub-mkrescue -d /usr/lib/grub/i386-pc -o build/Micos.iso build/grub

clean:
	@$(MAKE) -s -C kernel clean BASEDIR=kernel
