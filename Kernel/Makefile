include $(PROJECT_ROOT)/config.mk
include $(PROJECT_ROOT)/rules.mk

#Frequently changes
LINKER_SCRIPT := $(PLAT)-core.ld
SILLY_LIB := $(PROJECT_ROOT)/Library/libsilly
STANDALONE_LIB := $(SILLY_LIB)/Standalone
PROTOCOLS_LIB := $(SILLY_LIB)/Protocols/SillyOS

##################################################################################################
#							File structure dependent
#				(Do not change unless you now what are you doing!)
##################################################################################################
# Define where the code is
PLAT_ASM_SRC := $(wildcard Platform/$(PLAT)/Assembly/*.asm)
PLAT_ASM_SRC += $(wildcard Platform/$(PLAT)/Assembly/**/*.asm)

PLAT_CXX_SRC := $(wildcard Platform/$(PLAT)/*.cxx)
PLAT_CXX_SRC += $(wildcard Platform/$(PLAT)/**/*.cxx)

PLAT_OBJ := $(patsubst %.asm, %.o, $(PLAT_ASM_SRC))
PLAT_OBJ += $(patsubst %.cxx, %.o, $(PLAT_CXX_SRC))

CORE_SRC := $(wildcard Core/*.cxx)
CORE_SRC += $(wildcard Core/**/*.cxx)

CORE_OBJ := $(patsubst %.cxx, %.o, $(CORE_SRC))
#################################################################################################
C_FLAG := -std=c++11  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin 
#Do not use C stdlib use C++ one
C_FLAG += -nostdinc
# Target triple
C_FLAG += -target $(PLAT)-none-elf
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
C_FLAG += -I $(STANDALONE_LIB)
C_FLAG += -I $(PROTOCOLS_LIB)
C_FLAG += -I $(PROJECT_ROOT)/Kernel/Platform/$(PLAT)/Include

LD_FLAG := -T $(LINKER_SCRIPT) -nostdlib -z max-page-size=0x1000 

#Fake target
all: $(BUILD_DIR)/$(CORE_FILE)

#Link kernel
$(BUILD_DIR)/$(CORE_FILE): $(PLAT_OBJ) 
	$(LD) $(LD_FLAG) -o $@ $^ $(C_LIB)
#Clean up the source tree
clean:
	@rm -fvr $(PLAT_OBJ)
	@rm -fvr $(CORE_OBJ)

.force:
