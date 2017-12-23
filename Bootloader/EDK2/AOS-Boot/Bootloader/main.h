#ifndef _MAIN_H_
#define _MAIN_H_

#include <Uefi.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>

#include "conifg.h"

//status check marco
#define CHECK(X)\
(if(EFI_ERROR(X)){\
Print(L"Fail\n");\
Print(L"** Reason: %R", X);\
return X;\
})


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

const char* pixel_format[] = {
	"PixelRedGreenBlueReserved8BitPerColor",
	"PixelBlueGreenRedReserved8BitPerColor",
	"PixelBitMask",
	"PixelBltOnly",
	"PixelFormatMax"
};

#define MAGIC 0x1a2b3c4d
#define PLATFORM_EFI 0x1
#define CONTENT_VERSION 0x1a
typedef struct{
	UINT8 Platform;
	UINT32 Checksum;
	UINT8 Version;
	//Kernel
	VOID *KernelAddress;
	UINT64 KernelSize;
	//Video
	UINT32 VideoHeight;
	UINT32 VideoWidth;
	UINT64 FrameBufferBase;
	UINT64 FrameBufferSize;
	UINT32 PixelPerScanLine;
	UINT8 ColorFormat;
	EFI_PIXEL_BITMASK *Bitmask;
	//Memory
	EFI_MEMORY_DESCRIPTOR *MemMap;
	UINT64 MemMapSize;
	UINT64 DesSize;
	//ACPI

	//Partitions
	//UINT32 Partition_number;
	//UINT64 *Partition_table;
	//UEFI services
	EFI_RUNTIME_SERVICES *RuntimeServices;
	EFI_CONFIGURATION_TABLE *ConfigurationTable;
} AOS_BOOT_HEADER;

typedef void kernel_entry(UINT32, UINT64);

#endif
