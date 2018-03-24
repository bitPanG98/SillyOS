include $(PROJECT_ROOT)/config.mk

%.o: %.cxx
	@echo "[\033[0;32mCC\033[0m] <= \033[0;33m$<\033[0m"
	@$(CC) $(C_FLAG) -c $< -o $@ $(C_LIB)

# Assembly code
%.o: %.asm
	@echo "[\033[0;32mASM\033[0m] <= \033[0;33m$<\033[0m"
	@$(NASM) -f elf64 $< -o $@