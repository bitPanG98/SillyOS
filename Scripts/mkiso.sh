#!/bin/bash
cd $BUILD_DIR
if [ -e "fat.img" ]
then
    rm fat.img
fi

dd if=/dev/zero of=fat.img bs=1k count=1440
mformat -i fat.img -f 1440 ::
#make dirs in the image
mmd -i fat.img ::/efi
mmd -i fat.img ::/efi/boot
#copy bootloader
mcopy -i fat.img bootx64.efi ::/efi/boot
#copy kernel
mcopy -i fat.img ./*-sillyos.core ::/

if [ -e "iso" ]
then
    rm -R iso
fi
mkdir iso
cp fat.img iso
xorriso -as mkisofs -R -f -e fat.img -no-emul-boot -o $BUILD_ROOT/sillyos.iso iso