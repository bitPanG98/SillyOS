include ../Config.mk

LINKER_SCRIPT := $(PLAT)-core.ld

PLAT_ASM_SRC := $(wildcard Platform/$(PLAT)/asm/*.asm)
PLAT_ASM_SRC += $(wildcard Platform/$(PLAT)/asm/**/*.asm)

PLAT_CXX_SRC := $(wildcard Platform/$(PLAT)/*.cxx)
PLAT_CXX_SRC += $(wildcard Platform/$(PLAT)/**/*.cxx)

PLAT_OBJ := $(patsubst %.asm, %.o, $(PLAT_ASM_SRC))
PLAT_OBJ += $(patsubst %.cxx, %.o, $(PLAT_CXX_SRC))

CORE_SRC := $(wildcard Core/*.cxx)
CORE_SRC += $(wildcard Core/**/*.cxx)

CORE_OBJ := $(patsubst %.cxx, %.o, $(CORE_SRC))

C_FLAG := -std=c++11  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin -nostdinc
LD_FLAG :=  -nostdlib -z max-page-size=0x1000

C_LIB := 
ifeq ($(TOOL), LLVM)
# LLVM
C_FLAG += -target x86_64-pc-none-elf
C_LIB := -lc
else
# GCC
C_FLAG += -I $(PROJECT_ROOT)/CC/lib/gcc/x86_64-elf/7.3.0/include
C_LIB := -lgcc
endif
C_FLAG += -fno-rtti -fno-exceptions
C_FLAG += -O2 
C_FLAG +=  -Wall -Wextra
# Include dirs
C_FLAG += -I $(PROJECT_ROOT)/Library/Include 
C_FLAG += -I $(PROJECT_ROOT)/Kernel/Platform/$(PLAT)/Include

all: $(BUILD_DIR)/$(CORE_FILE)

$(BUILD_DIR)/$(CORE_FILE): $(PLAT_OBJ) 
	@echo "[\033[0;32mLinker\033[0m] <= \033[0;33mCore objects + Platform objects\033[0m"
	@$(LD)  -T $(LINKER_SCRIPT) $(LD_FLAG) -o $@ $(PLAT_OBJ) $(C_LIB)

%.o: %.cxx
	@echo "[\033[0;32mCC\033[0m] <= \033[0;33m$<\033[0m"
	@$(CC) $(C_FLAG) -c $< -o $@ $(C_LIB)

# Assembly code
%.o: %.asm
	@echo "[\033[0;32mASM\033[0m] <= \033[0;33m$<\033[0m"
	@$(NASM) -f elf64 $< -o $@

clean:
	@rm -fvr $(PLAT_OBJ)
	@rm -fvr $(CORE_OBJ)

.force:
