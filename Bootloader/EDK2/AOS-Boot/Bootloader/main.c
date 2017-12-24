//File: Bootloader.c
//Author: KeyboardMayCry
//Last update: 18 / 12 / 2017
#include "main.h"

AOS_BOOT_HEADER boot_hdr;

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST){

	EFI_STATUS status;
	UINTN KernelSize;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
	kernel_entry *Kernel = (kernel_entry *)KERNEL_ADDR;

	Print(L"AccessOS Bootloader\n");
	Print(L"Version: Beta\n");

	Print(L"Loading kernel...");
	status = LoadFileFromTheDrive(KERNEL_FILE, (VOID **)&Kernel, &KernelSize);
	CHECK(status);
	Print(L"Success");
	//Just let me know the size of kernel
	Print(L"Kernel Size: %d page (%d byte)\n", KernelSize/4096, KernelSize);

	Print(L"Getting GOProtocol...");
	status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GOP);
	CHECK(status);
	Print(L"Success");

	Print(L"Attempt to get better graphics setting...");
	UINTN info_size;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *gop_info;
	UINT32 max_mode = GOP->Mode->MaxMode;
	UINT32 biggest_ppsl = 0;
	UINT32 target_mode = 0;
	for (int i = 0; i < max_mode; ++i)
	{
		status = GOP->QueryMode(GOP, i, &info_size, &gop_info);
		if(!EFI_ERROR(status)){
			if ((gop_info->PixelsPerScanLine) > biggest_ppsl){
				biggest_ppsl = gop_info->PixelsPerScanLine;
				target_mode = i;
			}
		}
	}
	// Apply video mode
	status = GOP->SetMode(GOP, target_mode);
	CHECK(status);
	Print(L"Success");

	//	Get memory map
	EFI_MEMORY_DESCRIPTOR *MemMap;
	UINT64 MemMapSize = 0;
	UINT64 MapKey = 0;
	UINT64 DesSize  = 0;
	UINT32 DesVersion = 0;
	//Get memory map
	Print(L"Getting memory map...");
	status = GetMemMap(&MapKey, &DesVersion, &DesSize, &MemMap, &MemMapSize);
	CHECK(status);
	Print(L"Success");

	//put all needed things into a structure
	boot_hdr.Platform = PLATFORM_EFI;
	boot_hdr.Version = CONTENT_VERSION;
	//Kernel
	boot_hdr.KernelAddress = (VOID *)Kernel;
	boot_hdr.KernelSize = KernelSize;
	//Video
	boot_hdr.VideoHeight = gop_info->VerticalResolution;
	boot_hdr.VideoWidth = gop_info->HorizontalResolution;
	boot_hdr.FrameBufferBase = GOP->Mode->FrameBufferBase;
	boot_hdr.FrameBufferSize = GOP->Mode->FrameBufferSize;
	boot_hdr.PixelPerScanLine = gop_info->PixelsPerScanLine;
	boot_hdr.PixelFormat = (UINT8)gop_info->PixelFormat;
	//BitMask is only available when PixelFormat is PixelBitMask.
	if (gop_info->PixelFormat == PixelBitMask){
		boot_hdr.Bitmask = gop_info->PixelInformation;;
	}

	boot_hdr.MemoryMap = MemMap;
	boot_hdr.MemoryMapSize = MemMapSize;
	boot_hdr.DescriptorSize = DesSize;

	boot_hdr.Checksum = sizeof(boot_hdr);


	Print(L"=== Critical Area ===");
	Print(L"If you stuck, that mean we failed to boot up.  :/");

	Print(L"Disconnecting BootServices...");
	status = ST->BootServices->ExitBootServices(IH, MapKey);
    CHECK(status);

	/***	WARNING!	WARNING!	WARNING!	WARNING!	WARNING!	WARNI***/
	
	/***			DO	NOT	PUT	ANY	BOOT SERVICES	FUNCTION	BELOW				***/
	/***	If we passed status check, then BootServices is no longer usable.	***/
	
	/***	WARNING!	WARNING!	WARNING!	WARNING!	WARNING!	WAR	***/

    ST->RuntimeServices->SetVirtualAddressMap(MemMapSize, DesSize, DesVersion, MemMap);

	//See you in Kernel :)
	Kernel(MAGIC, (UINT64)&boot_hdr);

	return EFI_SUCCESS; //We'll never go here, but we must make compiler happy ;)
}

EFI_STATUS GetMemMap(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR **Memmap, UINT64 *MemmapSize){
	//lazy..
	EFI_STATUS status;
	UINT64 Size = 0;
	UINT64 Pages = 1;
	//Get Memory Map Size frist 
	while(1){
		status = gBS->AllocatePages(AllocateAnyPages, EfiLoaderData, Pages, (UINT64 *)*Memmap);
		if(status != EFI_SUCCESS){
			return status;
		}
		Size = Pages * 4096;
		status = gST->BootServices->GetMemoryMap(&Size, *Memmap, Key, DesSize, DesVersion);
		if(status == EFI_BUFFER_TOO_SMALL){
			Pages++;
		}else if(status == EFI_SUCCESS){
			*MemmapSize = Size;
			return status;
		}else{
			return status;
		}
	}
	return EFI_SUCCESS;
}

EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size){

	EFI_STATUS status;
	EFI_HANDLE *handles = NULL;
	EFI_FILE *root = NULL;
	EFI_FILE *file = NULL;
	EFI_FILE_INFO *info = NULL;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFS = NULL;
	UINTN MaxHandles;
	UINTN InfoBuffSize = 0;
	
	status = gBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleFileSystemProtocolGuid, NULL, &MaxHandles, &handles);
	if(EFI_ERROR(status)){
		return status;
	}
	for(UINTN i = 0; i < MaxHandles; i++){
		status = gBS->HandleProtocol(handles[i], &gEfiSimpleFileSystemProtocolGuid, (void **)&SFS);
		if(EFI_ERROR(status)){
			return status;
		}
		status = SFS->OpenVolume(SFS, &root);
		if(EFI_ERROR(status)){
			return status;
		}
		//check is needed file exist?
		status = root->Open(root, &file, FileName, EFI_FILE_MODE_READ, 0);
		if(EFI_ERROR(status)){
			//found!
			break;
		}
	}

	//Release
	gBS->FreePool(handles);

	//still nothing...
	if(file == NULL){
		return status;
	}

	//Get what size of buffer it need.
	status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, NULL);
	if(status == EFI_BUFFER_TOO_SMALL){
		//Need more space!
		status = gBS->AllocatePool(EfiBootServicesData, InfoBuffSize, (VOID **)&info);
		if(EFI_ERROR(status)){
		return status;
	}
	}else if(EFI_ERROR(status)){
		return status;
	}

	//if go here, mean sucess to allocate pool.
	//do the real getinfo().
	status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, info);
	if(EFI_ERROR(status)){
		return status;
	}	
	*Size = info->FileSize;
	//Not use it any more, u free!
	gBS->FreePool(info);

	status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, *Size / 4096, *Data);
	if(EFI_ERROR(status)){
		return status;
	}
	
	//Read file
	status = file->Read(file, Size, (UINT8 *)*Data);
	if(EFI_ERROR(status)){
		return status;
	}
	
	//Finish!
	status = file->Close(file);
	if(EFI_ERROR(status)){
		return status;
	}
	root->Close(root);

	return EFI_SUCCESS;
}