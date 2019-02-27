#1/ON : 0/OFF
DEBUG ?= 1
# Platform
BOOT_TYPE ?= EFI
## Files
#kernel
KERNEL_FILE := x86_64-sillyos.core
#image
ISO_FILE ?= sillyos.iso
## Tools
# C++ compiler
CC := clang++
# Linker
LD := ld.lld
# Assembler
NASM := nasm
