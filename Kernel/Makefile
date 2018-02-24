include ../Config.mk

LINKER_SCRIPT := $(PLAT)-core.ld

PLAT_ASM_SRC := $(wildcard Platform/$(PLAT)/asm/*.asm)
PLAT_ASM_SRC += $(wildcard Platform/$(PLAT)/asm/**/*.asm)

PLAT_CPP_SRC := $(wildcard Platform/$(PLAT)/*.cpp)
PLAT_CPP_SRC += $(wildcard Platform/$(PLAT)/**/*.cpp)

PLAT_OBJ := $(patsubst %.asm, %.o, $(PLAT_ASM_SRC))
PLAT_OBJ += $(patsubst %.cpp, %.o, $(PLAT_CPP_SRC))

CORE_SRC := $(wildcard Core/*.cpp)
CORE_SRC += $(wildcard Core/**/*.cpp)

CORE_OBJ := $(patsubst %.cpp, %.o, $(CORE_SRC))

ifeq ($(PLAT), x86_64)
C_FLAG := -target x86_64-none-elf
endif
C_FLAG += -ffreestanding -fno-builtin -nostdlib -nostdinc -nostdinc++ -fno-rtti -mno-red-zone -fno-exceptions -O2
C_FLAG += -Wall -std=c++11
# stdlib
C_FLAG += -I $(BUILD_ROOT)/Library/include -I $(BUILD_ROOT)/Kernel/Platform/$(PLAT)/include

LD_FLAG := --gc-sections

all: $(BUILD_DIR)/$(CORE_FILE)

$(BUILD_DIR)/$(CORE_FILE): $(PLAT_OBJ) 
	$(LD)  -T $(LINKER_SCRIPT) $(LD_FLAG) $(PLAT_OBJ) $(CORE_A) -o $@


%.o: %.cpp
	$(CC) $(C_FLAG) $< -o $@

# Assembly code
%.o: %.asm
	$(NASM) -f elf64 $< -o $@

clean:
	@xargo clean
	@rm -fvr $(PLATFORM_OBJ)

.force:
