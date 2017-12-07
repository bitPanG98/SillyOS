
#1/on 0/off
DEBUG ?= 1

# Platform
ARCH ?= x86_64
TARGET ?= $(ARCH)-sillyos

# Files
OUTPUT_DIR := ./Build
CORE := $(OUTPUT_DIR)/$(TARGET).core
ISO ?= $(OUTPUT_DIR)/$(TARGET).iso

# Path
LINKER_SCRIPT := ./Stuff/$(TARGET).ld

# Tools
LD := ld
NASM := nasm