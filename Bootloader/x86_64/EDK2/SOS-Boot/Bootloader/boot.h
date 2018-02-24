/*
3==========================================D
    @File:	boot.h
    @Path:  /Bootloader/x86_64/EDK2/SOS-Boot/Bootloader
    @Authors:   KeyboardMayCry[eddy199883@gmail.com]
    @Descriptions:  
    @Updates:
        04 Feb 2018	||	KeyboardMayCry	||	File Created. 
3==========================================D
*/
#ifndef _BOOT_H_
#define _BOOT_H_

#include <Uefi.h>

#define EFI_RGBR 1 //Red Green Blue Reserved
#define EFI_BGRR 2 //Blue Green Red Reserved
#define BITMASK 3

#define KERNEL_ADDR 0x100000
#define KERNEL_FILE L"\\x86_64-sillyos.core"

typedef struct{
    UINT64 Checksum;
	UINT32 VerticalResolution;
    UINT32 HorizontalResolution;
    UINT64 FrameBufferBase;
    UINT64 FrameBufferSize;
	UINT8 PixelSize;
    UINT8 RIndex;
	UINT8 GIndex;
	UINT8 BIndex;
} __attribute__((packed)) SOS_BOOT_VIDEO_INFO;

#define MAGIC 0x1a2b3c4d
#define PLATFORM_EFI 0x1
#define CONTENT_VERSION 0x1

typedef struct{
	UINT32 Magic;
    UINT8 Platform;
    UINT64 Checksum;
    UINT8 Version;
	//Kernel
	VOID *KernelAddress;
	UINT64 KernelSize;
	//Video
	SOS_BOOT_VIDEO_INFO *VideoInfo;
	//Memory
	VOID *MemoryMap;
	UINT64 MemoryMapSize;
	UINT64 DescriptorSize;
	//Tables
	UINT8 AcpiVersion;
	VOID *RSDP;
	//UEFI only
	VOID *RuntimeServices;
} __attribute__((packed)) SOS_BOOT_INFO;

#endif