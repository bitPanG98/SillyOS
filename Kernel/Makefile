include $(PROJECT_ROOT)/config.mk
include $(PROJECT_ROOT)/rules.mk

#Frequently changes
LINKER_SCRIPT := core.ld
SILLY_LIB := $(PROJECT_ROOT)/libsilly

##################################################################################################
#							File structure dependent
#				(Do not change unless you now what are you doing!)
##################################################################################################
# Define where the code is
PLAT_ASM_SRC := $(wildcard Assembly/*.asm)
PLAT_ASM_SRC += $(wildcard Assembly/**/*.asm)

KERNEL_SRC := $(wildcard *.cxx)
KERNEL_SRC += $(wildcard **/*.cxx)

KERNEL_OBJ := $(patsubst %.cxx, %.o, $(KERNEL_SRC))
KERNEL_OBJ += $(patsubst %.asm, %.o, $(PLAT_ASM_SRC))
#################################################################################################
C_FLAG := -std=c++11  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin 
#Do not use C stdlib use C++ one
C_FLAG += -nostdinc
# Target triple
C_FLAG += -target x86_64-none-elf
# Libraries search path
C_LIB := -L $(BUILD_DIR)
# Disable C++ Runtime including exceptions
C_FLAG += -fno-rtti -fno-exceptions
# Optimization level
C_FLAG += -O2 
# Warnings really important? YES
C_FLAG +=  -Wall -Wextra
# Header search path
C_FLAG += -I $(SILLY_LIB)
C_FLAG += -I $(PROJECT_ROOT)/Kernel/Include

LD_FLAG := -T $(LINKER_SCRIPT) -nostdlib -z max-page-size=0x1000 

#Fake target
all: $(BUILD_DIR)/$(KERNEL_FILE)

#Link kernel
$(BUILD_DIR)/$(KERNEL_FILE): $(KERNEL_OBJ) 
	$(LD) $(LD_FLAG) -o $@ $^ $(C_LIB)
#Clean up the source tree
clean:
	@rm -fvr $(KERNEL_OBJ)

.force:
