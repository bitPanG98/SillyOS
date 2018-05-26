#ifndef _SILLYOS_H_
#define _SILLYOS_H_

#include <Uefi.h>

#define EFI_RGBR 1 //Red Green Blue Reserved
#define EFI_BGRR 2 //Blue Green Red Reserved
#define BITMASK 3

#define KERNEL_ADDR 0x100000
#define KERNEL_FILE L"\\x86_64-sillyos.core"

typedef struct{
    UINT32 Checksum;
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
#define PLATFORM_LEGACY 0x2
#define CONTENT_VERSION 0x1

typedef struct{
	UINT32 Magic;
    UINT8 Platform;
    UINT32 Checksum;
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
	VOID *RSDP;
	//UEFI only
	VOID *RuntimeServices;
} __attribute__((packed)) SOS_BOOT_INFO;

#define SOS_PAGE_TYPE_4K 1
#define SOS_PAGE_TYPE_2M 2
#define SOS_PAGE_TYPE_1G 3

#define SOS_MEM_TYPE_UNUSABLE 0
#define SOS_MEM_TYPE_ACPI 1
#define SOS_MEM_TYPE_IO 2
#define SOS_MEM_TYPE_KERNAL 3
#define SOS_MEM_TYPE_MODULE 4
#define SOS_MEM_TYPE_USERLAND 5
#define SOS_MEM_TYPE_FREE 6

typedef struct {
	UINT64 PhyStart;
	UINT64 VirtStart;
	UINT64 Number;
	UINT64 PageType;
	UINT64 Type;
} __attribute__((packed)) SOS_MEM_INFO;

#endif