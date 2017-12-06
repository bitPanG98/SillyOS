include Makefiles/Config.mk

#Platform specificed code
ifeq ($(ARCH), x86_64)
include Makefiles/Platform/x86_64/x86_64.mk
include Makefiles/Platform/x86_64/Bootloader.mk
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

run: $(BOOTLOADER) $(CORE)
#qemu
clean: kernel_clean platform_clean bootloader_clean
	@echo Cleaning done.

$(CORE): $(PLATFORM_OBJ) kernel_core
	@echo Linking Kernel...
	