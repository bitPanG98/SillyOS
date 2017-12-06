include Makefiles/Config.mk

#Platform specificed code
ifeq ($(ARCH), x86_64)
include Makefiles/x86_64.mk
endif
#Kernel core
#Path of libKernel.a
ifeq ($(DEBUG), 0)
LIB_KERNEL_A := Kernel/target/$(TARGET)/release/libKernel.a
else
LIB_KERNEL_A := Kernel/target/$(TARGET)/debug/libKernel.a
endif
include Makefiles/Core.mk

####################################
#	TARGETS	AHEAD
####################################
.PHONY: all clean
all: run clean

run: bootloader $(CORE)
#qemu
clean: kernel_clean platform_clean
	@echo Cleaning done.

bootloader:
	@echo Building Boot Loader...
	#Ubuntu's 'sh' did not contain 'source' command
	bash ./Stuff/edk2.sh

$(CORE): $(PLATFORM_OBJ) kernel_core
	@echo Linking Kernel...
	