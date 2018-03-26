include $(PROJECT_ROOT)/config.mk
include $(PROJECT_ROOT)/rules.mk

#libsilly
SILLY_ASM_SRC := $(wildcard Silly/asm/*.asm)
SILLY_ASM_SRC += $(wildcard Silly/asm/**/*.asm)

SILLY_CXX_SRC := $(wildcard Silly/*.cxx)
SILLY_CXX_SRC += $(wildcard Silly/**/*.cxx)

SILLY_OBJ := $(patsubst %.asm, %.o, $(SILLY_ASM_SRC))
SILLY_OBJ += $(patsubst %.cxx, %.o, $(SILLY_CXX_SRC))

#libstd
STANDARD_ASM_SRC := $(wildcard Standard/asm/*.asm)
STANDARD_ASM_SRC += $(wildcard Stardard/asm/**/*.asm)

STANDARD_CXX_SRC := $(wildcard Standard/*.cxx)
STANDARD_CXX_SRC += $(wildcard Standard/**/*.cxx)

STANDARD_OBJ := $(patsubst %.asm, %.o, $(STANDARD_ASM_SRC))
STANDARD_OBJ += $(patsubst %.cxx, %.o, $(STANDARD_CXX_SRC))

C_FLAG := -std=c++14  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin -nostdinc
C_FLAG += -I $(PROJECT_ROOT)/Library/Silly/Include
C_FLAG += -I $(PROJECT_ROOT)/CC/lib/gcc/$(PLAT)-elf/**/include

LIB_SILLY_A := $(BUILD_DIR)/libsilly.a
LIB_STANDARD := $(BUILD_DIR)/libstd.a

silly: $(SILLY_OBJ)
	@echo "[\033[0;32mAR\033[0m] <= \033[0;33mLibrary objects\033[0m"
	@$(AR) rcs $(LIB_SILLY_A) $^
standard:
	@echo 'Not done yet!!!'
	exit

clean:
	@rm -fvr $(SILLY_OBJ)
	@rm -fvr $(STANDARD_OBJ)