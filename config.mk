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
CC := $(PLAT)-elf-g++
LD := $(PLAT)-elf-ld
AR := $(PLAT)-elf-ar
NASM := nasm
