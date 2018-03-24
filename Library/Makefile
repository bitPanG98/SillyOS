include $(PROJECT_ROOT)/config.mk
include $(PROJECT_ROOT)/rules.mk

#libsilly
SILLY_ASM_SRC := $(wildcard Silly/asm/*.asm)
SILLY_ASM_SRC += $(wildcard Silly/asm/**/*.asm)

SILLY_CXX_SRC := $(wildcard Silly/*.cxx)
SILLY_CXX_SRC += $(wildcard Silly/**/*.cxx)

#libstd
STANDARD_ASM_SRC := $(wildcard Standard/asm/*.asm)
STANDARD_ASM_SRC += $(wildcard Stardard/asm/**/*.asm)

STANDARD_CXX_SRC := $(wildcard Standard/*.cxx)
STANDARD_CXX_SRC += $(wildcard Standard/**/*.cxx)

C_FLAG := -std=c++11  -ffreestanding  -mno-red-zone -nostdlib -fno-builtin -nostdinc

LIB_SILLY_A := $(BUILD_DIR)/libsilly.a
LIB_STANDARD := $(BUILD_DIR)/libstd.a

silly:
	echo 'Not done yet!!!'
	exit
standard:
	@echo 'Not done yet!!!'
	exit