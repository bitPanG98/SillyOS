include Config.mk

default: CreateDirs bootloader kernel

pack:
	@echo Packing... 

kernel: .force CreateDirs
	@echo Building kernel...
	@$(MAKE) -C Kernel

bootloader: .force CreateDirs
ifeq ($(BOOT_TYPE), EFI)
	@echo Building bootloader... Type: EFI
	@$(MAKE) -C ./Bootloader/x86_64/EDK2
endif
ifeq ($(BOOT_TYPE), LEGACY)
	@echo Building bootloader... Type: Legacy
	@$(MAKE) -C ./Bootloader/x86_64/Legacy
endif
ifeq ($(BOOT_TYPE), GRUB)
	@echo Building bootloader... Type: Grub
endif

iso: .force bootloader kernel
	@Scripts/mkiso.sh

qemu: .force iso
	@sudo qemu-system-$(PLAT) -L ./ -bios /usr/share/ovmf/OVMF.fd -drive file=Build/fat.img -m 5G

CreateDirs: .force 
	@echo Creating output dirs...
	@mkdir -p $(BUILD_DIR)

clean:
	@echo Cleaning...
ifneq ($(BOOT_TYPE), EFI)
	@$(MAKE) -C ./Bootloader/x86_64/Legacy clean
endif
	@$(MAKE) -C Kernel clean

	
.force:
