include Makefile_config/config.mk

#Path of libKernel.a
ifeq ($(DEBUG), 0)
LIB_KERNEL_A := Kernel/target/$(TARGET)/release/libKernel.a
else
LIB_KERNEL_A := Kernel/target/$(TARGET)/debug/libKernel.a
endif

all: run

run: bootloader kernel

clean:
	@echo Cleaning Kernel...
	@cd Kernel && xargo clean

bootloader:
	@echo Building Boot Loader...
	#Ubuntu's 'sh' did not contain 'source' command
	bash edk2.sh

kernel: $(LIB_KERNEL_A)
	@echo Building Kernel...
	
#Kernel itself
$(LIB_KERNEL_A):
	@cd Kernel && xargo build --target $(TARGET)