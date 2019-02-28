include config.mk

default: CreateDirs bootloader kernel

pack:
	@echo Packing... 

kernel: .force CreateDirs
	@$(MAKE) -s -C Kernel

bootloader: .force CreateDirs
ifeq ($(BOOT_TYPE), EFI)
	@$(MAKE) -s -C ./Bootloader/EDK2
endif
ifeq ($(BOOT_TYPE), LEGACY)
	@$(MAKE) -s -C ./Bootloader/Legacy
endif

libsilly:
#discard for now
	@$(MAKE) -s -C silly
	@echo skipped

efi_iso: .force bootloader kernel
	@rm -fvr $(BUILD_DIR)/efi.img
	@dd if=/dev/zero of=$(BUILD_DIR)/efi.img bs=1M count=50
	@mkfs.vfat $(BUILD_DIR)/efi.img -F32
	@mmd -i $(BUILD_DIR)/efi.img ::/efi
	@mmd -i $(BUILD_DIR)/efi.img ::/efi/boot
ifeq ($(BOOT_TYPE), GRUB)
#NDY
	@mcopy -i $(BUILD_DIR)/efi.img $(BUILD_DIR)/bootloader.efi ::/efi/boot
else
	@mv $(BUILD_DIR)/bootloader.efi $(BUILD_DIR)/bootx64.efi
	@mcopy -i $(BUILD_DIR)/efi.img $(BUILD_DIR)/bootx64.efi ::/efi/boot
endif
	@mcopy -i $(BUILD_DIR)/efi.img $(BUILD_DIR)/*.core ::/
	@mkdir $(BUILD_DIR)/iso
	@cp -f $(BUILD_DIR)/efi.img $(BUILD_DIR)/iso
	@xorriso -as mkisofs -R -f -e efi.img -no-emul-boot -o $(PROJECT_ROOT)/sillyos.iso $(BUILD_DIR)/iso

qemu: .force efi_iso
	@sudo qemu-system-x86_64  -serial stdio -cpu Haswell  -bios /usr/share/ovmf/x64/OVMF_CODE.fd  -drive file=./sillyos.iso -m 2G

CreateDirs: .force clean
	@mkdir -p $(BUILD_DIR)

clean:
	@echo Cleaning...
	@rm -fvr $(BUILD_DIR)
ifneq ($(BOOT_TYPE), EFI)
	@$(MAKE) -C ./Bootloader/Legacy clean
endif
	@$(MAKE) -C Kernel clean
	@$(MAKE) -C libsilly clean

	
.force:
