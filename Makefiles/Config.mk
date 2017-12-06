
#1/on 0/off
DEBUG ?= 1

# Platform
ARCH ?= x86_64
TARGET ?= $(ARCH)-sillyos

# Files
CORE := $(TARGET).core
ISO ?= $(TARGET).iso

# Tools
LD := 
NASM := nasm