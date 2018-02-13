include ../Config.mk

LINKER_SCRIPT := $(PLAT)-core.ld

ASM_SRC := $(wildcard src/asm/*.asm)
ASM_OBJ := $(patsubst %.asm, %.o, $(ASM_SRC))

CORE_A := target/$(TARGET)/release/libKernel.a

LD_FLAG := -nostdlib --gc-sections

all: $(BUILD_DIR)/$(CORE_FILE)

$(BUILD_DIR)/$(CORE_FILE): .force make_core $(ASM_OBJ)
	$(LD)  -T $(LINKER_SCRIPT) $(LD_FLAG) $(ASM_OBJ) $(CORE_A) -o $@

make_core: .force
	RUST_TARGET_PATH=$(shell pwd) xargo build --target $(TARGET) --release


# Assembly code
%.o: %.asm
	$(NASM) -f elf64 $< -o $@

clean:
	@xargo clean
	@rm -fvr $(PLATFORM_OBJ)

.force:
