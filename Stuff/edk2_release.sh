#!/bin/sh
#if edk2 not found
if [ -e "./edk2/edksetup.sh" ]
then
	echo EDK2 found
else
	echo EDK2 not found
	git clone git://github.com/tianocore/edk2
	# 2017-12-5: Patching is needed, see edk2_fix.path
	# 				GenSec can't pass the compilation cuz 
	#				inside the "edk2/BaseTools/Source/C/Makefiles/header.makefile",
	#				compiler compile files with -Werror, so any warning could pause the process.
	#				The fix is simple, just reomove '-Werror' and it work just fine.
	#				Dunno how wrong this move could be :\ 
	make -C ./edk2/BaseTools
fi
echo Copying needed files...
cp -r ./Bootloader/EDK2/AOS-Boot ./edk2/
cd edk2 && source ./edksetup.sh && build -b RELEASE -p AOS-Boot/AOS-Bootloader.dsc -q -t GCC5 -a X64
