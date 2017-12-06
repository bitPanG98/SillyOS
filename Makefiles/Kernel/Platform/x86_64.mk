PLATFORM_DIR := ./Kernel/Platform/x86_64
PLATFORM_SRC := $(wildcard $(PLATFORM_DIR)/src/*.asm)
PLATFORM_OBJ := $(patsubst $(PLATFORM_DIR)/src/%.asm, $(PLATFORM_DIR)/src/%.o, $(PLATFORM_SRC))

$(PLATFORM_DIR)/%.o: $(PLATFORM_DIR)/%.asm
	@echo Compiling x86_64 code... $<
	@$(NASM) -f elf64 $< -o $@ 

platform_clean:
	@echo Cleaning Platform code...
	@rm -fv $(PLATFORM_OBJ)