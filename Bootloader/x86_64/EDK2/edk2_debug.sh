#!/bin/bash
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

if [ -e "./edk2/SOS-Boot" ] 
then 
	rm -fR ./edk2/SOS-Boot
fi
echo Cleaning output...
if [ -e "./edk2/Build" ]
then
	rm -fR ./edk2/Build
fi
echo Copying needed files...
cp -r ./SOS-Boot ./edk2/

cd edk2 && source edksetup.sh && build --buildtarget=DEBUG -p SOS-Boot/SOS-Bootloader.dsc -s -q -t GCC5 -a X64 -d 0 && cp -r ./Build/SOS/DEBUG_GCC5/X64/SOS-Bootloader.efi $BUILD_DIR/bootloader.efi

