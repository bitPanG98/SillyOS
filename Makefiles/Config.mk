
#1/on 0/off
DEBUG ?= 1

# Platform
ARCH ?= x86_64
TARGET ?= $(ARCH)-sillyos

# Files
CORE := $(TARGET).core
ISO ?= $(TARGET).iso
BOOTLOADER := ./edk2/Build/AOS/DEBUG_GCC5/X64/AOS-Bootloader.efi

# Tools
LD := 
NASM := nasm