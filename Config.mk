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
CC := clang-5.0
else
CC := x86_64-elf-g++
endif
LD := x86_64-elf-g++
AR := ar
NASM := nasm
