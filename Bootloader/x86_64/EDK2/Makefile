include ../../../Config.mk

EDK2_SCRIPT := ./edk2_release.sh
ifeq ($(DEBUG), 1)
EDK2_SCRIPT := ./edk2_debug.sh
endif

all:
	@bash $(EDK2_SCRIPT)