include $(PROJECT_ROOT)/config.mk

%.o: %.cxx
	$(CC) $(C_FLAG) -c $< -o $@ $(C_LIB)

# Assembly code
%.o: %.asm
	$(NASM) -f elf64 $< -o $@