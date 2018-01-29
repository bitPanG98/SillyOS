include ../Config.mk

LINKER_SCRIPT := $(PLAT)-core.ld

LIB_KERNAL_A := ./target/$(TARGET)/debug/libKernel.a
ifeq ($(DEBUG), 0)
LIB_KERNAL_A := ./target/$(TARGET)/release/libKernel.a
endif

PLATFORM_DIR := ./Platform/$(PLAT)
PLATFORM_SRC := $(wildcard $(PLATFORM_DIR)/**/*.asm)
PLATFORM_OBJ := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(PLATFORM_SRC))

LD_FLAG := -nostdlib --gc-sections

all: build_dir $(BUILD_DIR)/$(CORE_FILE)

build_dir: .force
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(CORE_FILE): .force $(LIB_KERNAL_A) $(PLATFORM_OBJ)
	@$(LD) -T $(LINKER_SCRIPT) $(LD_FLAG) $(PLATFORM_OBJ) $(LIB_KERNAL_A) -o $@

$()

# Assembly code
$(PLATFORM_OBJ): $(PLATFORM_SRC)
ifeq ($(PLAT), x86_64)
	@$(NASM) -f elf64 $< -o $@
endif

clean:
	xargo clean
	@rm -fvr $(BUILD_DIR)

.force: