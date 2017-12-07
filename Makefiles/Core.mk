#Common Core building method

#Kernel itself
$(LIB_KERNEL_A):
	@echo Building Core... 
	@cd Kernel && xargo build --target $(TARGET)

kernel_clean: 
	@echo Cleaning Kernel...
	@cd Kernel && xargo clean