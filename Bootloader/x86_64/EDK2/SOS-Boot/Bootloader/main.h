/*
3==========================================D
    @File:	main.h
    @Path:  /Bootloader/x86_64/EDK2/SOS-Boot/Bootloader
    @Authors:   KeyboardMayCry[eddy199883@gmail.com]
    @Descriptions:  
    @Updates:
        12 Jan 2018	||	KeyboardMayCry	||	File Created. 
        04 Feb 2018 ||  KeyboardMayCry  ||  Boot info. moved to boot.h
3==========================================D
*/
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Uefi.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include <Guid/Acpi.h>

#include <elf.h>

#include "sillyos.h"

//status check marco
#define CHECK(X) 	{	\
if(EFI_ERROR(X)) {Print(L"Fail\n**Reason: %r\n", X);	return X;}}

// const char *EFIMemMapText[] = { 
// 	"ReservedMemory         ", 
//     "LoaderCode             ", 
//     "LoaderData             ", 
//     "BootServicesCode       ", 
//     "BootServicesData       ", 
//     "RuntimeServicesCode    ", 
//     "RuntimeServicesData    ", 
//     "ConventionalMemory     ", 
//     "UnusableMemory         ", 
//     "ACPIReclaimMemory      ", 
//     "ACPIMemoryNVS          ", 
//     "MemoryMappedIO         ", 
//     "MemoryMappedIOPortSpace", 
//     "PalCode                ",
//     "PersistentMemory       ", 
//     "MaxMemory              "
// };

#define DEFAULT_HR 1280
#define DEFAULT_VR 720


typedef void KERNEL_ENTRY(SOS_BOOT_INFO *);
//main.c
EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size);
EFI_STATUS GetMemMap(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR **Memmap, UINT64 *MemmapSize);

//loader.c
EFI_STATUS load_kernel(VOID **kernel, UINTN *kmem_size, UINTN *kfile_size);
UINT8 is_ELF(Elf64_Ehdr elf_header);

#endif
