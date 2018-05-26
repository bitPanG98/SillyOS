include $(PROJECT_ROOT)/config.mk
include $(PROJECT_ROOT)/rules.mk

LINKER_SCRIPT := $(PLAT)-core.ld

PLAT_ASM_SRC := $(wildcard src/Assembly/$(PLAT)/*.asm)
PLAT_ASM_SRC += $(wildcard src/Assembly/$(PLAT)/**/*.asm)

PLAT_OBJ := $(patsubst %.asm, %.o, $(PLAT_ASM_SRC))

ifeq ($(DEBUG), 1)
RUST_OBJ := $(PWD)/Kernel/target/x86_64-sillyos/debug/libKernel.a
else
RUST_OBJ := $(PWD)/Kernel/target/x86_64-sillyos/release/libKernel.a
endif

LD_FLAG :=  -nostdlib -z max-page-size=0x1000 --gc-section

all: $(BUILD_DIR)/$(CORE_FILE)

$(BUILD_DIR)/$(CORE_FILE): $(PLAT_OBJ) $(RUST_OBJ)
	@echo "[\033[0;32mLinker\033[0m] <= \033[0;33mCore objects + Platform objects\033[0m"
	@$(LD) -T $(LINKER_SCRIPT) $(LD_FLAG) -o $@ $^

$(RUST_OBJ): .force
	@echo "[\033[0;32mLinker\033[0m] <= \033[0;33mCore objects + Platform objects\033[0m"
ifeq ($(DEBUG), 1)
	@RUST_TARGET_PATH=$(PWD)/Kernel xargo build --target x86_64-sillyos
else
	@RUST_TARGET_PATH=$(PWD)/Kernel xargo build --target x86_64-sillyos --release
endif

clean:
	@rm -fvr $(PLAT_OBJ)
	@RUST_TARGET_PATH=$(PWD)/Kernel xargo clean

.force:
