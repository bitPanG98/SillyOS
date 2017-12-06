 # Bootloader makefile for x86_64 platform

$(BOOTLOADER):
	@echo Building EFI Boot Loader...
	#Ubuntu's 'sh' did not contain 'source' command
	bash ./Stuff/edk2.sh

bootloader_clean:
	@echo Cleaning Bootloader...
	rm -vf $(BOOTLOADER)
