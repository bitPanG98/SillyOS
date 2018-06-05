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
#pragma once
#include <Types.h>

typedef struct {
    u32 Checksum;
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
    u32 Checksum;
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
    void *RSDP;
    // UEFI only
    void *RuntimeServices;
} __attribute__((packed)) SOS_BOOT_INFO;

