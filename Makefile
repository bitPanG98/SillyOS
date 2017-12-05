include Makefile_config/config.mk

all: disk

disk: bootloader kernel

clean:
	@echo Cleaning Kernel...
	@cd Kernel && xargo clean

bootloader:
	@echo Building Boot Loader...

kernel:
	@echo Building Kernel...
	
#Kernel itself
:
	@cd Kernel && xargo build --target $(TARGET)