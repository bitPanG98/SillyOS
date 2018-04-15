#1/ON : 0/OFF
DEBUG ?= 1
# Platform
PLAT ?= x86_64
TARG ?= $(PLAT)-sillyos
BOOT_TYPE ?= EFI
# Files
CORE_FILE := $(TARG).core
ISO_FILE ?= sillyos.iso
# Tools
TOOL := GCC
ifeq ($(TOOL), LLVM)
CC := $(PROJECT_ROOT)/cross-llvm/build/llvm/bin/clang
LD := $(PROJECT_ROOT)/cross-llvm/build/llvm/bin/ld.lld
else
CC := $(PLAT)-elf-g++
LD := $(PLAT)-elf-g++
endif

AR := $(PLAT)-elf-ar
NASM := nasm
