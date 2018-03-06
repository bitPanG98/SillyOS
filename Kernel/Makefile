include ../Config.mk

LINKER_SCRIPT := $(PLAT)-core.ld

PLAT_ASM_SRC := $(wildcard Platform/$(PLAT)/asm/*.asm)
PLAT_ASM_SRC += $(wildcard Platform/$(PLAT)/asm/**/*.asm)

PLAT_CPP_SRC := $(wildcard Platform/$(PLAT)/*.c)
PLAT_CPP_SRC += $(wildcard Platform/$(PLAT)/**/*.c)

PLAT_OBJ := $(patsubst %.asm, %.o, $(PLAT_ASM_SRC))
PLAT_OBJ += $(patsubst %.c, %.o, $(PLAT_CPP_SRC))

CORE_SRC := $(wildcard Core/*.c)
CORE_SRC += $(wildcard Core/**/*.c)

CORE_OBJ := $(patsubst %.c, %.o, $(CORE_SRC))

LD_FLAG :=  -nostdlib -z max-page-size=0x1000

# C_FLAG := -target x86_64-pc-none-elf
C_FLAG += -std=c11  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin -nostdinc
# C_FLAG += -fno-rtti -fno-exceptions
C_FLAG += -O2 
C_FLAG +=  -Wall
# stdlib
C_FLAG += -I $(PROJECT_ROOT)/Library/Include 
C_FLAG += -I $(PROJECT_ROOT)/Kernel/Platform/$(PLAT)/Include

CRTBEGIN := $(shell $(CC) $(C_FLAG) -print-file-name=crtbegin.o)
CRTEND := $(shell $(CC) $(C_FLAG) -print-file-name=crtend.o)

all: $(BUILD_DIR)/$(CORE_FILE)

$(BUILD_DIR)/$(CORE_FILE): $(PLAT_OBJ) 
	$(LD)  -T $(LINKER_SCRIPT) $(LD_FLAG)  $(PLAT_OBJ) $(CORE_A)  -o $@ -lgcc

%.o: %.c
	$(CC) $(C_FLAG) -c $< -o $@

# Assembly code
%.o: %.asm
	$(NASM) -f elf64 $< -o $@

clean:
	@rm -fvr $(PLAT_OBJ)
	@rm -fvr $(CORE_OBJ)

.force:
