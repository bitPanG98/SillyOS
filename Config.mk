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
CC := x86_64-elf-g++
LD := x86_64-elf-ld
AR := ar
NASM := nasm
