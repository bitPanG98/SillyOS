#ifndef _LIBRARYS_H_
#define _LIBRARYS_H_

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

const char* pixel_format[5] = {
	"PixelRedGreenBlueReserved8BitPerColor",
	"PixelBlueGreenRedReserved8BitPerColor",
	"PixelBitMask",
	"PixelBltOnly",
	"PixelFormatMax"
};

#define MAGIC "MAGIC"
typedef struct{
	char Magic[8];

	UINT32 VideoHeight;
	UINT32 VideoWidth;

	UINT64 FrameBufferBase;
	UINT64 FrameBufferSize;
	UINT32 PixelPerScanLine;
	
	UINT8 ColorFormat;
	UINT32 RedMask;
	UINT32 GreenMask;
	UINT32 BlueMask;
	UINT32 ReservedMask;

	EFI_MEMORY_DESCRIPTOR *MemMap;
	UINT64 MemMapSize;
	UINT64 DesSize;

    	UINT64 *MLAddress;
	//we need to know what ML size is 
	UINT64 MLSize;
	//ACPI

	//Partitions
	UINT32 Partition_number;
	UINT64 *Partition_table;
	//UEFI services
	EFI_RUNTIME_SERVICES *RuntimeServices;
	EFI_CONFIGURATION_TABLE *ConfigurationTable;
} AOS_BOOT_HEADER;

#endif
