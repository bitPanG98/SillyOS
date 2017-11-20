//File: Bootloader.c
//Author: KeyboardMayCry
//Last update: 22 / 5 / 2017


#include "Librarys.h"

#define ML_ADDR 0x100000

AOS_BOOT_HEADER boot_hdr;

EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size);
EFI_STATUS GetMemMap(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR **Memmap, UINT64 *MemmapSize);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST)
{
	
	EFI_STATUS status;
	VOID *Loader = (VOID*)ML_ADDR;
	UINTN LoaderSize;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;

	Print(L"AccessOS Bootloader\n");
	Print(L"Version: Alpha\n");

	//Load Loader
	status = LoadFileFromTheDrive(L"\\Loader\\kernel.bin", &Loader, &LoaderSize);
	if(status != EFI_SUCCESS) {
		Print(L"Fail to load kernel.");
		ST->BootServices->Exit(IH, status, 0, NULL);
	}
	Print(L"Loader Size: %d byte\n", LoaderSize);
	Print(L"Loader pages: %d \n", LoaderSize/4096);
	//toKernel = Loader;

	status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GOP);
	if(status != EFI_SUCCESS) {
		Print(L"Can't locate GOP");
		ST->BootServices->Exit(IH, status, 0, NULL);
	}
	//#TODO: Get EDID
	//Try to get better graphics setting
	UINTN info_size;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *gop_info;
	UINT32 max_mode = GOP->Mode->MaxMode;
	UINT32 biggest_ppsl = 0;
	UINT32 target_mode = 0;
	for (int i = 0; i < max_mode; ++i)
	{
		status = GOP->QueryMode(GOP, i, &info_size, &gop_info);
		if(status == EFI_SUCCESS){
			if ((gop_info->PixelsPerScanLine) > biggest_ppsl){
				biggest_ppsl = gop_info->PixelsPerScanLine;
				target_mode = i;
			}
		}
	}
	if(status != EFI_SUCCESS){
		Print(L"Can't change video mode.");
		ST->BootServices->Exit(IH, status, 0, NULL);
	}

	status = GOP->SetMode(GOP, target_mode);
	if(status != EFI_SUCCESS) {
		Print(L"Can't apply new video mode");
		ST->BootServices->Exit(IH, status, 0, NULL);
	}

	/*	Get memory for EFI and us
	*	Because of our memory map has been corrupted, so we need to do it again.
	*/
	//we not sure this address is "usable", but still better than a constant.
	EFI_MEMORY_DESCRIPTOR *MemMap;
	UINT64 MemMapSize = 0;
	UINT64 MapKey = 0;
	UINT64 DesSize  = 0;
	UINT32 DesVersion = 0;
	//Get memory map for SetVirtualAddressMap() and ExitBootServices().
	status = GetMemMap(&MapKey, &DesVersion, &DesSize, &MemMap, &MemMapSize);
	if(status != EFI_SUCCESS){
		Print(L"Can't get memory map.\n");
		ST->BootServices->Exit(IH, status, 0, NULL);
	}
	//box->MemMap = MemMap;

	Print(L"If you stuck, that mean we failed to boot up.  :/");

	status = ST->BootServices->ExitBootServices(IH, MapKey);
    	if (status != EFI_SUCCESS)
    	{
    		Print(L"Fail to call ExitBootServices(), Reason: %r\n", status);
    		ST->BootServices->Exit(IH, status, 0, NULL);
    	}

    	ST->RuntimeServices->SetVirtualAddressMap(MemMapSize, DesSize, DesVersion, MemMap);

	return EFI_SUCCESS; //We'll never go here, but we must make compiler happy ;)
}

EFI_STATUS GetMemMap(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR **Memmap, UINT64 *MemmapSize){

	//lazy..
	EFI_STATUS status;
	UINT64 Size = 0;
	UINT64 Pages = 1;
	//Get Memory Map Size frist
	while(1){
		status = gBS->AllocatePages(AllocateAnyPages, EfiBootServicesData, Pages, (UINT64 *)*Memmap);
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

EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size)
{
	EFI_STATUS status;
	EFI_HANDLE *handles = NULL;
	EFI_FILE *root = NULL;
	EFI_FILE *file = NULL;
	EFI_FILE_INFO *info = NULL;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFS = NULL;
	UINTN MaxHandles;
	UINTN InfoBuffSize = 0;
	
	status = gBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleFileSystemProtocolGuid, NULL, &MaxHandles, &handles);
	if(status != EFI_SUCCESS){
		return status;
	}
	for(UINTN i = 0; i < MaxHandles; i++){
		status = gBS->HandleProtocol(handles[i], &gEfiSimpleFileSystemProtocolGuid, (void **)&SFS);
		if(status != EFI_SUCCESS){
			return status;
		}
		status = SFS->OpenVolume(SFS, &root);
		if(status != EFI_SUCCESS){
			return status;
		}
		//check is needed file exist?
		status = root->Open(root, &file, FileName, EFI_FILE_MODE_READ, 0);
		if(status != EFI_SUCCESS){
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
		status = gBS->AllocatePool(EfiLoaderData, InfoBuffSize, (VOID **)&info);
		if(status != EFI_SUCCESS){
		return status;
	}
	}else if(status != EFI_SUCCESS){
		return status;
	}

	//if go here, mean sucess to allocate pool.
	//do the real getinfo().
	status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, info);
	if(status != EFI_SUCCESS){
		return status;
	}	
	*Size = info->FileSize;
	//Not use it any more, u free!
	gBS->FreePool(info);

	status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, *Size / 4096, *Data);
	if(status != EFI_SUCCESS){
		return status;
	}
	
	//Read file
	status = file->Read(file, Size, (UINT8 *)*Data);
	if(status != EFI_SUCCESS){
		return status;
	}
	
	//Finish!
	status = file->Close(file);
	if(status != EFI_SUCCESS){
		return status;
	}
	root->Close(root);

	return EFI_SUCCESS;
}