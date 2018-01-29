/*
3==========================================D
    @File:	main.c
    @Path:  /Bootloader/x86_64/EDK2/AOS-Boot/Bootloader
    @Authors:   KeyboardMayCry[eddy199883@gmail.com]
    @Descriptions:  
    @Updates:
        12 Jan 2018	||	KeyboardMayCry	||	File Created. 
3==========================================D
*/
#include "main.h"

static SOS_BOOT_INFO boot_info;
static SOS_BOOT_INFO_HEADER boot_hdr;
static SOS_BOOT_VIDEO_INFO boot_video;

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST){

	EFI_STATUS status;
	UINTN KernelSize;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
	kernel_entry *KernelEntry = (kernel_entry *)KERNEL_ADDR;
	Print(L"SillyOS Bootloader\n");
	Print(L"Version: Beta\n");

	/*
		FUTURE TASK
		Read config file and mode submition
	*/
	Print(L"Getting GOProtocol...");
	status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GOP);
	CHECK(status);
	Print(L"Success\n");

	Print(L"Attempt to get better graphics setting...\n");
	UINTN info_size;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *gop_info = GOP->Mode->Info;
	UINT32 max_mode = GOP->Mode->MaxMode;
	Print(L"[Current] HR: %d VR: %d PF: %d PPSL: %d\n", gop_info->HorizontalResolution, gop_info->VerticalResolution,\
	gop_info->PixelFormat, gop_info->PixelsPerScanLine);
	UINT32 target_mode = 0;
	for (int i = 0; i < max_mode; ++i)
	{
		status = GOP->QueryMode(GOP, i, &info_size, &gop_info);
		Print(L"Mode %d HR: %d VR: %d PF: %d PPSL: %d\n", i, gop_info->HorizontalResolution, \
		gop_info->VerticalResolution, gop_info->PixelFormat, gop_info->PixelsPerScanLine );
		
		if (!EFI_ERROR(status) && gop_info->PixelFormat != PixelBltOnly && gop_info->PixelFormat < PixelBitMask) //ignore BitMask for now
		{
			if(gop_info->HorizontalResolution == DEFAULT_HR && gop_info->VerticalResolution == DEFAULT_VR){
				target_mode = i;
				break;
			}
		}
	}
	// Apply video mode
	status = GOP->SetMode(GOP, target_mode);
	CHECK(status);
	Print(L"Success\n");
	//clear screen
	ST->ConOut->ClearScreen(ST->ConOut);

	Print(L"Loading kernel...");
	status = LoadFileFromTheDrive(KERNEL_FILE, (VOID**)&KernelEntry, &KernelSize);
	CHECK(status);
	//Just let me know the size of kernel
	Print(L"Kernel Size: %d byte\n", KernelSize);
	//Validate kernel
	// status = ValidateELF((VOID **)&KernelEntry);
	// CHECK(status);
	// Print(L"Success\n");

	//	Getting ACPI tables
	Print(L"Fetching ACPI Tables...");
	EFI_CONFIGURATION_TABLE *CT = ST->ConfigurationTable;
	EFI_GUID Acpi20_guid = EFI_ACPI_20_TABLE_GUID;
	EFI_GUID Acpi10_guid = ACPI_10_TABLE_GUID;
	//EFI_GUID Smbios_guid = SMBIOS3_TABLE_GUID;
	UINT64 Acpi_signature = EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER_SIGNATURE;
	EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER *RSDP = NULL;
	UINT8 Acpi_version = 0;
	for(UINTN i = 0; i < ST->NumberOfTableEntries; i++){
		//Print(L"%g\n", CT[i].VendorGuid);
		if (CompareGuid(&(CT[i].VendorGuid), &Acpi20_guid) == TRUE ||
			CompareGuid(&(CT[i].VendorGuid), &Acpi10_guid) == TRUE)
		{
			RSDP = (EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER *)(CT[i].VendorTable);
				
			if (RSDP->Signature == Acpi_signature)
			{	 //RSDP found
				 if (RSDP->Revision == EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION)
				{ //Revsion matched
					//Print(L"\nACPI version: 2\n");
					Acpi_version = EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION;
					break;
				}
				else if (RSDP->Revision == 0)
				{
					//Print(L"\nACPI version: 1\n");
					Acpi_version = 1;
					break;
				}
			}
		}
		RSDP = NULL;
		CT++; //next
	}
	//check table
	if(RSDP == NULL || Acpi_version == 0){
		CHECK(EFI_NOT_FOUND);
	}
	Print(L"Success\n");
	

	Print(L"=== Critical Area ===\n");
	Print(L"If you stuck, that mean we failed to boot up.  :/ \n");

	//	Get memory map
	EFI_MEMORY_DESCRIPTOR *MemMap = (EFI_MEMORY_DESCRIPTOR *)0x1000;
	UINT64 MemMapSize = 0;
	UINT64 MapKey = 0;
	UINT64 DesSize = 0;
	UINT32 DesVersion = 0;
	//Get memory map
	Print(L"Getting memory map and terminating BootServices...");
	status = GetMemMap(&MapKey, &DesVersion, &DesSize, &MemMap, &MemMapSize);
	CHECK(status);
	//Do not put any calls between GetMemMap() and ExitBootServices()!
	for(int i = 0; i<5;i++){
	status = ST->BootServices->ExitBootServices(IH, MapKey);
	if(!EFI_ERROR(status)){
		break;
	}
	}
	CHECK(status);

	/***	WARNING!	WARNING!	WARNING!	WARNING!	WARNING!	WARNI***/
	
	/***			DO	NOT	PUT	ANY	BOOT SERVICES	FUNCTION	BELOW				***/
	/***	If we passed status check, then BootServices is no longer usable.	***/
	
	/***	WARNING!	WARNING!	WARNING!	WARNING!	WARNING!	WAR	***/

    //ST->RuntimeServices->SetVirtualAddressMap(MemMapSize, DesSize, DesVersion, MemMap);

    //put all needed things into a structure
	boot_hdr.Magic = MAGIC;
	boot_hdr.Platform = PLATFORM_EFI;
	boot_hdr.Version = CONTENT_VERSION;

	boot_info.Header = &boot_hdr;

	//Kernel
	boot_info.KernelAddress = (UINT64 *)KernelEntry;
	boot_info.KernelSize = KernelSize;
	//Video
	boot_video.VerticalResolution = gop_info->VerticalResolution;
	boot_video.HorizontalResolution = gop_info->HorizontalResolution;
	boot_video.FrameBufferBase = GOP->Mode->FrameBufferBase;
	boot_video.FrameBufferSize = GOP->Mode->FrameBufferSize;
	boot_video.MaxX = gop_info->PixelsPerScanLine;
	boot_video.Bitmask = 0;
	switch(gop_info->PixelFormat){
		case PixelRedGreenBlueReserved8BitPerColor:
			boot_video.PixelType = EFI_RGBR;
			break;
		case PixelBlueGreenRedReserved8BitPerColor:
			boot_video.PixelType = EFI_BGRR;
			break;
		/*case PixelBitMask:
			boot_info.PixelType = BITMASK;
			boot_info.Bitmask = (UINT32)((UINT8)(gop_info->PixelInformation->RedMask) ;
			break;*/
		default:
			break;
	}

	boot_info.VideoInfo = &boot_video;

	boot_info.MemoryMap = (UINT64 *)MemMap;
	boot_info.MemoryMapSize = MemMapSize;
	boot_info.DescriptorSize = DesSize;
	//ACPI Table
	boot_info.AcpiVersion = Acpi_version;
	boot_info.RSDP = (UINT64 *)RSDP;

	boot_info.RuntimeServices = (UINT64 *)(ST->RuntimeServices);

	//calculate ckecksum
	boot_hdr.Checksum = -(boot_hdr.Magic + boot_hdr.Platform + boot_hdr.Version +
						   *(boot_info.KernelAddress) + boot_info.KernelSize +
						   boot_video.VerticalResolution + boot_video.HorizontalResolution +
						   boot_video.FrameBufferBase + boot_video.FrameBufferSize +
						   boot_video.MaxX + boot_video.Bitmask + boot_video.PixelType +
						   *(boot_info.MemoryMap) + boot_info.MemoryMapSize +
						   boot_info.DescriptorSize + *(boot_info.RSDP) + *(boot_info.RuntimeServices));

	//test video buff
	// UINT32 *vb = (UINT32 *)boot_video.FrameBufferBase;
	// for(int i = 0; i < boot_video.HorizontalResolution; i++){
	// 	*vb = 0xff0000;
	// 	vb++;
	// }


	//See you in Kernel :)
	KernelEntry(&boot_info);

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
		//Print(L"\n1\n");
		return status;
	}
	for(UINTN i = 0; i < MaxHandles; i++){
		status = gBS->HandleProtocol(handles[i], &gEfiSimpleFileSystemProtocolGuid, (void **)&SFS);
		if(EFI_ERROR(status)){
			//Print(L"\n2\n");
			return status;
		}
		status = SFS->OpenVolume(SFS, &root);
		if(EFI_ERROR(status)){
			//Print(L"\n3\n");
			return status;
		}
		//check is needed file exist?
		status = root->Open(root, &file, FileName, EFI_FILE_MODE_READ, 0);
		if(status == EFI_SUCCESS){
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
			//Print(L"\n4\n");
			return status;
	}
	}else if(EFI_ERROR(status)){
		//Print(L"\n5\n");
		return status;
	}

	//if go here, mean sucess to allocate pool.
	//do the real getinfo().
	status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, info);
	if(EFI_ERROR(status)){
		//Print(L"\n6\n");
		return status;
	}	
	*Size = info->FileSize;
	gBS->FreePool(info);

	status = gBS->AllocatePool(EfiLoaderData, *Size, Data);
	if(EFI_ERROR(status)){
		//Print(L"\n7\n");
		return status;
	}

			 //Read file
	status = file->Read(file, Size, (UINT8 *)*Data);
	if(EFI_ERROR(status)){
		//Print(L"\n8\n");
		return status;
	}
	
	//Finish!
	status = file->Close(file);
	if(EFI_ERROR(status)){
		//Print(L"\n9\n");
		return status;
	}
	root->Close(root);

	return EFI_SUCCESS;
}

EFI_STATUS ValidateELF64(VOID **buff){
	return EFI_SUCCESS;
}