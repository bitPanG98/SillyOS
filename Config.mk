#1/ON : 0/OFF
DEBUG ?= 1

# Platform
PLAT ?= x86_64
TARGET ?= $(PLAT)-sillyos
BOOT_TYPE ?= EFI

# Files
BUILD_DIR := Build
CORE_FILE := $(TARGET).core
ISO_FILE ?= sillyos.iso

# Tools
CC := $(PLAT)-elf-g++
LD := $(PLAT)-elf-ld
NASM := nasm
