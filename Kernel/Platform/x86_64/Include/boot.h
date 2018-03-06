/*
3==========================================D
    @File:	boot.hpp
    @Path:  /Kernel/Platform/x86_64/include
    @Authors:   KeyboardMayCry[eddy199883@gmail.com]
    @Descriptions:
    @Updates:
        20 Feb 2018	||	KeyboardMayCry	||	File Created.
3==========================================D
*/
#ifndef _BOOT_H_
#define _BOOT_H_
#include <types.h>

typedef struct {
    u64 Checksum;
    u32 VerticalResolution;
    u32 HorizontalResolution;
    u64 FrameBufferBase;
    u64 FrameBufferSize;
    u8 PixelSize;
    u8 RIndex;
    u8 GIndex;
    u8 BIndex;
} __attribute__((packed)) SOS_BOOT_VIDEO_INFO;

#define MAGIC 0x1a2b3c4d
#define PLATFORM_EFI 0x1
#define CONTENT_VERSION 0x1

typedef struct {
    u32 Magic;
    u8 Platform;
    u64 Checksum;
    u8 Version;
    // Kernel
    void *KernelAddress;
    u64 KernelSize;
    // Video
    SOS_BOOT_VIDEO_INFO *VideoInfo;
    // Memory
    void *MemoryMap;
    u64 MemoryMapSize;
    u64 DescriptorSize;
    // Tables
    u8 AcpiVersion;
    void *RSDP;
    // UEFI only
    void *RuntimeServices;
} __attribute__((packed)) SOS_BOOT_INFO;

#endif
