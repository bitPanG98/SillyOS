#1/ON : 0/OFF
DEBUG ?= 1
# Platform
PLAT ?= x86_64
TARGET ?= $(PLAT)-sillyos
BOOT_TYPE ?= EFI
# Files
CORE_FILE := $(TARGET).core
ISO_FILE ?= sillyos.iso
# Tools
TOOL := GCC
ifeq ($(TOOL), LLVM)
CC := $(PROJECT_ROOT)/cross-llvm/build/llvm/bin/clang
LD := $(PROJECT_ROOT)/cross-llvm/build/llvm/bin/ld.lld
else
CC := x86_64-elf-g++
LD := x86_64-elf-g++
endif

AR := ar
NASM := nasm