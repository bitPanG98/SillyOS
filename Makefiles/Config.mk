
#1/on 0/off
DEBUG ?= 1

# Platform
ARCH ?= x86_64
TARGET ?= $(ARCH)-sillyos

# Files
BUILD_DIR := ./Build
TEMP_DIR := ./temp
CORE := $(BUILD_DIR)/$(TARGET).core
ISO ?= $(BUILD_DIR)/$(TARGET).iso

# Path
LINKER_SCRIPT := ./Stuff/$(ARCH)-core.ld

# Tools
LD := ld
NASM := nasm