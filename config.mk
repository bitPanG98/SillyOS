#1/ON : 0/OFF
DEBUG ?= 1
# Platform
PLAT ?= x86_64
TARG ?= $(PLAT)-sillyos
BOOT_TYPE ?= EFI
## Files
#kernel
CORE_FILE := $(TARG).core
#image
ISO_FILE ?= sillyos.iso
## Tools
# C++ compiler
CC := clang++
# Linker
LD := ld.lld
# Assembler
NASM := nasm
