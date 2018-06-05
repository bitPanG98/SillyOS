include $(PROJECT_ROOT)/config.mk
include $(PROJECT_ROOT)/rules.mk

LINKER_SCRIPT := $(PLAT)-core.ld

PLAT_ASM_SRC := $(wildcard Platform/$(PLAT)/Assembly/*.asm)
PLAT_ASM_SRC += $(wildcard Platform/$(PLAT)/Assembly/**/*.asm)

PLAT_CXX_SRC := $(wildcard Platform/$(PLAT)/*.cxx)
PLAT_CXX_SRC += $(wildcard Platform/$(PLAT)/**/*.cxx)

PLAT_OBJ := $(patsubst %.asm, %.o, $(PLAT_ASM_SRC))
PLAT_OBJ += $(patsubst %.cxx, %.o, $(PLAT_CXX_SRC))

CORE_SRC := $(wildcard Core/*.cxx)
CORE_SRC += $(wildcard Core/**/*.cxx)

CORE_OBJ := $(patsubst %.cxx, %.o, $(CORE_SRC))

C_FLAG := -std=c++11  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin 
#Do not use C stdlib use C++ one
C_FLAG += -nostdinc
C_FLAG += -I $(PROJECT_ROOT)/Library/Silly/Include
C_FLAG += -target $(PLAT)-none-elf

C_LIB := -L $(BUILD_DIR)

C_FLAG += -fno-rtti -fno-exceptions
C_FLAG += -O2 
C_FLAG +=  -Wall -Wextra
# Include
C_FLAG += -I $(PROJECT_ROOT)/Library/libsilly/Standalone
C_FLAG += -I $(PROJECT_ROOT)/Kernel/Platform/$(PLAT)/Include

LD_FLAG := -T $(LINKER_SCRIPT) -nostdlib -z max-page-size=0x1000 

all: $(BUILD_DIR)/$(CORE_FILE)

$(BUILD_DIR)/$(CORE_FILE): $(PLAT_OBJ) 
	$(LD) $(LD_FLAG) -o $@ $^ $(C_LIB)

clean:
	@rm -fvr $(PLAT_OBJ)
	@rm -fvr $(CORE_OBJ)

.force:
