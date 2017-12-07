include Makefiles/Config.mk

#Kernel core
#Path of libKernel.a
ifeq ($(DEBUG), 0)
LIB_KERNEL_A := Kernel/target/$(TARGET)/release/libKernel.a
else
LIB_KERNEL_A := Kernel/target/$(TARGET)/debug/libKernel.a
endif
#leave it the last.
include Makefiles/Core.mk

#Platform specificed code(PSCode)
ifeq ($(ARCH), x86_64)
#Contain bootloader and PSCode building method of x86_64.
include Makefiles/x86_64.mk
else
#Contain bootloader and PSCode building method of RPi.
endif


####################################
#	TARGETS	AHEAD
####################################
.PHONY: create_build iso

all: create_build iso

create_build:
	@echo Creating output dirs...
	@mkdir -p $(OUTPUT_DIR)

iso: bootloader $(CORE)

# Cleaning
clean: $(OUTPUT_DIR)
	@echo Cleaning...
	@rm -R $(OUTPUT_DIR)
purge: clean kernel_clean platform_clean 
	@echo Purging...
	
	