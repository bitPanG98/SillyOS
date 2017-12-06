
#Kernel itself
kernel_core:
	@echo Building Core... 
	#@cd Kernel && xargo build --target $(TARGET)

kernel_clean: 
	@echo Cleaning Kernel...
	@cd Kernel && xargo clean