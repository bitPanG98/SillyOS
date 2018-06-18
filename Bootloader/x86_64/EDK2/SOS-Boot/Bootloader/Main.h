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

/*
    This file located in "Library/libsilly/Protocols/SillyOS"
*/
#define __UEFI_BOOTLOADER__
#include "Booting.h"

//status check marco
#define CHECK(X) 	{	\
if(EFI_ERROR(X)) {Print(L"Fail\n**Reason: %r\n", X);	return X;}}

#define DEFAULT_HR 1280
#define DEFAULT_VR 720

#define EFI_RGBR 1 //Red Green Blue Reserved
#define EFI_BGRR 2 //Blue Green Red Reserved
#define BITMASK 3

#define KERNEL_ADDR 0x100000
#define KERNEL_FILE L"\\x86_64-sillyos.core"

typedef void KERNEL_ENTRY(SOS_BOOT_INFO *);
//Main.c
EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size);
EFI_STATUS GetMemMap(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR **Memmap, UINT64 *MemmapSize);

//ELF_Loader.c
EFI_STATUS load_kernel(VOID **kernel, UINTN *kmem_size, UINTN *kfile_size);
UINT8 is_ELF(Elf64_Ehdr elf_header);

#endif
