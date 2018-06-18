#pragma once

/*  When included by EFI boot loader*/
#ifdef __UEFI_BOOTLOADER__
    #include <Uefi.h>
    /* Replacing types*/
    #define U8  UINT8
    #define U16 UINT16
    #define U32 UINT32
    #define U64 UINT64

    #define I8 INT8
    #define I16 INT16
    #define I32 INT32
    #define I64 INT64
#else
    #include <Types.h>
    /* Replacing types*/
    #define VOID void
    #define U8  u8
    #define U16 u16
    #define U32 u32
    #define U64 u64

    #define I8 i8
    #define I16 i16
    #define I32 i32
    #define I64 i64
#endif

typedef struct{
    U32 Checksum;
	U32 VerticalResolution;
    U32 HorizontalResolution;
    U64 FrameBufferBase;
    U64 FrameBufferSize;
	U8 PixelSize;
    U8 RIndex;
	U8 GIndex;
	U8 BIndex;
} __attribute__((packed)) SOS_BOOT_VIDEO_INFO;

#define MAGIC 0x1a2b3c4d
#define PLATFORM_EFI 0x1
#define PLATFORM_LEGACY 0x2
#define CONTENT_VERSION 0x1

typedef struct{
	U32 Magic;
    U8 Platform;
    U32 Checksum;
    U8 Version;
	//Kernel
	VOID *KernelAddress;
	U64 KernelSize;
	//Video
	SOS_BOOT_VIDEO_INFO *VideoInfo;
	//Memory
	VOID *MemoryMap;
	U64 MemoryMapSize;
	U64 DescriptorSize;
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
	U64 PhyStart;
	U64 VirtStart;
	U64 Number;
	U64 PageType;
	U64 Type;
} __attribute__((packed)) SOS_MEM_INFO;