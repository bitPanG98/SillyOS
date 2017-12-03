ARCH ?= x86_64
TARGET ?= $(ARCH)-sillyos
CORE := $(TARGET).core
ISO ?= $(TARGET).iso

all: disk

disk: bootloader kernel

clean:
	cd Kernel && xargo clean

bootloader:
	@echo Building Boot Loader...
kernel:
	@echo Building Kernel...
	cd Kernel && xargo build --target $(TARGET)
	