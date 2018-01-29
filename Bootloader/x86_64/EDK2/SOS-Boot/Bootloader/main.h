/*
3==========================================D
    @File:	Makefile
    @Path:  /Bootloader/x86_64/EDK2/Legacy
    @Authors:   KeyboardMayCry[eddy199883@gmail.com]
    @Descriptions:  
    @Updates:
        12 Jan 2018	||	KeyboardMayCry	||	File Created. 
3==========================================D
*/
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Uefi.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include <Guid/Acpi.h>

#include <elf.h>

//status check marco
#define CHECK(X) 	{	\
if(EFI_ERROR(X)) {Print(L"Fail\n**Reason: %r\n", X);	return X;}}

const char *EFIMemMapText[] = { 
	"ReservedMemory         ", 
    "LoaderCode             ", 
    "LoaderData             ", 
    "BootServicesCode       ", 
    "BootServicesData       ", 
    "RuntimeServicesCode    ", 
    "RuntimeServicesData    ", 
    "ConventionalMemory     ", 
    "UnusableMemory         ", 
    "ACPIReclaimMemory      ", 
    "ACPIMemoryNVS          ", 
    "MemoryMappedIO         ", 
    "MemoryMappedIOPortSpace", 
    "PalCode                ",
    "PersistentMemory       ", 
    "MaxMemory              "
};

#define DEFAULT_HR 1280
#define DEFAULT_VR 720

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
    UINT32 MaxX;
    UINT8 PixelType;
    UINT32 Bitmask;
}SOS_BOOT_VIDEO_INFO;

typedef struct{
	UINT32 Magic;
    UINT8 Platform;
    UINT64 Checksum;
    UINT8 Version;
}SOS_BOOT_INFO_HEADER;

#define MAGIC 0x1a2b3c4d
#define PLATFORM_EFI 0x1
#define CONTENT_VERSION 0x1
typedef struct{
	SOS_BOOT_INFO_HEADER *Header;
	//Kernel
	UINT64 *KernelAddress;
	UINT64 KernelSize;
	//Video
	SOS_BOOT_VIDEO_INFO *VideoInfo;
	//Memory
	UINT64 *MemoryMap;
	UINT64 MemoryMapSize;
	UINT64 DescriptorSize;
	//Tables
	UINT8 AcpiVersion;
	UINT64 *RSDP;
	//UEFI only
	UINT64 *RuntimeServices;
} SOS_BOOT_INFO;

typedef void kernel_entry(SOS_BOOT_INFO *);

EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size);
EFI_STATUS GetMemMap(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR **Memmap, UINT64 *MemmapSize);

//EFI_STATUS ValidateELF64(VOID **);

#endif
