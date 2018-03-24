include config.mk

default: CreateDirs bootloader kernel

pack:
	@echo Packing... 

kernel: .force CreateDirs
	@echo "[\033[0;32mMake\033[0m] <= \033[0;33m'Make me a Kernel'\033[0m"
	@$(MAKE) -s -C Kernel

bootloader: .force CreateDirs
ifeq ($(BOOT_TYPE), EFI)
	@echo "[\033[0;32mMake\033[0m] <= \033[0;33m'Make me a EFI Bootloader'\033[0m"
	@$(MAKE) -s -C ./Bootloader/x86_64/EDK2
endif
ifeq ($(BOOT_TYPE), LEGACY)
	@echo "[\033[0;32mMake\033[0m] <= \033[0;33m'Make me a Legacy Bootloader'\033[0m"
	@$(MAKE) -s -C ./Bootloader/x86_64/Legacy
endif

library_silly:
	@echo "[\033[0;32mMake\033[0m] <= \033[0;33m'Make me a Silly Library'\033[0m"
	@$(MAKE) -s -C library silly

library_standard:
	@echo "[\033[0;32mMake\033[0m] <= \033[0;33m'Make me a Standard Library'\033[0m"
	@$(MAKE) -s -C library standard

efi_iso: .force bootloader kernel
	@echo "[\033[0;32mISO\033[0m] <= \033[0;33mSillyOS\033[0m"
	@rm -fvr $(BUILD_DIR)/efi.img
	@dd if=/dev/zero of=$(BUILD_DIR)/efi.img bs=1M count=50
	@mkfs.vfat $(BUILD_DIR)/efi.img -F32
	@mmd -i $(BUILD_DIR)/efi.img ::/efi
	@mmd -i $(BUILD_DIR)/efi.img ::/efi/boot
ifeq ($(BOOT_TYPE), GRUB)
	@mcopy -i $(BUILD_DIR)/efi.img $(BUILD_DIR)/bootloader.efi ::/efi/boot
else
	@mv $(BUILD_DIR)/bootloader.efi $(BUILD_DIR)/bootx64.efi
	@mcopy -i $(BUILD_DIR)/efi.img $(BUILD_DIR)/bootx64.efi ::/efi/boot
endif
	@mcopy -i $(BUILD_DIR)/efi.img $(BUILD_DIR)/*-sillyos.core ::/
	@mkdir $(BUILD_DIR)/iso
	@cp -f $(BUILD_DIR)/efi.img $(BUILD_DIR)/iso
	@xorriso -as mkisofs -R -f -e efi.img -no-emul-boot -o $(PROJECT_ROOT)/sillyos.iso $(BUILD_DIR)/iso

qemu: .force efi_iso
	@sudo qemu-system-$(PLAT)  -serial stdio -cpu Haswell  -bios /usr/share/ovmf/OVMF.fd  -drive file=./sillyos.iso -m 5G

CreateDirs: .force clean
	@mkdir -p $(BUILD_DIR)

clean:
	@echo Cleaning...
	@rm -fvr $(BUILD_DIR)
ifneq ($(BOOT_TYPE), EFI)
	@$(MAKE) -C ./Bootloader/x86_64/Legacy clean
endif
	@$(MAKE) -C Kernel clean

	
.force:
