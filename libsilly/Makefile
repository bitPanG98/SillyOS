include $(PROJECT_ROOT)/config.mk
include $(PROJECT_ROOT)/rules.mk

#libsilly
SILLY_ASM_SRC := $(wildcard Assembly/*.asm)
SILLY_ASM_SRC += $(wildcard Assembly/**/*.asm)

SILLY_C_SRC := $(wildcard *.c)
SILLY_C_SRC += $(wildcard **/*.c)

SILLY_OBJ := $(patsubst %.asm, %.o, $(SILLY_ASM_SRC))
SILLY_OBJ += $(patsubst %.c, %.o, $(SILLY_C_SRC))

STANDARD_OBJ := $(patsubst %.asm, %.o, $(STANDARD_ASM_SRC))
STANDARD_OBJ += $(patsubst %.c, %.o, $(STANDARD_C_SRC))

C_FLAG := -std=c++14  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin -nostdinc
C_FLAG += -I $(PROJECT_ROOT)/libsilly/**/**

LIB_SILLY_A := $(BUILD_DIR)/libsilly.a

silly: $(SILLY_OBJ)
	@echo "[\033[0;32mAR\033[0m] <= \033[0;33mLibrary objects\033[0m"
	@$(AR) rcs $(LIB_SILLY_A) $^
standard:
	@echo 'Not done yet!!!'
	exit

clean:
	@rm -fvr $(SILLY_OBJ)
