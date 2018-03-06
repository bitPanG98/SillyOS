#!/bin/bash
cd $BUILD_DIR
if [ -e "efi.img" ]
then
    rm efi.img
fi

dd if=/dev/zero of=efi.img bs=1M count=50
#format
mkfs.vfat efi.img -F32
#make dirs in the image
mmd -i efi.img ::/efi
mmd -i efi.img ::/efi/boot
#copy bootloader
mcopy -i efi.img bootx64.efi ::/efi/boot
#copy kernel
mcopy -i efi.img ./*-sillyos.core ::/

if [ -e "iso" ]
then
    rm -R iso
fi
mkdir iso
cp efi.img iso
xorriso -as mkisofs -R -f -e efi.img -no-emul-boot -o $PROJECT_ROOT/sillyos.iso iso