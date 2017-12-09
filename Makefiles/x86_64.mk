# Makefile for x86_64 platform
BOOTLOADER := $(OUTPUT_DIR)/efi/boot/bootx64.efi
ifeq ($(DEBUG), 1)
# In debug mode
EDK2_OUTPUT := ./edk2/Build/AOS/DEBUG_GCC5/X64/AOS-Bootloader.efi
EDK2_SCRIPT := ./Stuff/edk2_debug.sh
else
# In release mode
EDK2_OUTPUT := ./edk2/Build/AOS/RELEASE_GCC5/X64/AOS-Bootloader.efi
EDK2_SCRIPT := ./Stuff/edk2_release.sh
endif

# Assembly code
PLATFORM_DIR := ./Kernel/Platform/x86_64
PLATFORM_SRC := $(wildcard $(PLATFORM_DIR)/src/*.asm)
PLATFORM_OBJ := $(patsubst $(PLATFORM_DIR)/src/%.asm, $(PLATFORM_DIR)/src/%.o, $(PLATFORM_SRC))

###########################################
#	Public targets
##########################################
$(CORE): $(PLATFORM_OBJ) $(LIB_KERNEL_A)
	@echo Linking Kernel...
	#@$(LD)

bootloader: edk2_build
	@echo 	Copying Boot Loader...
	@mkdir -p $(OUTPUT_DIR)/efi/boot
	@cp -f $(EDK2_OUTPUT) $(BOOTLOADER)

platform_clean:
	@echo Cleaning Platform code...
	@rm -fv $(PLATFORM_OBJ)

###########################################
#	Internel targets
##########################################
$(PLATFORM_DIR)/%.o: $(PLATFORM_DIR)/%.asm
	@echo Compiling x86_64 code... $<
	@$(NASM) -f elf64 $< -o $@ 

edk2_build:
	@echo Building EFI Boot Loader...
	#Ubuntu's 'sh' did not contain 'source' command
	bash $(EDK2_SCRIPT)
