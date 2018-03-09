#include "main.h"

static SOS_BOOT_INFO boot_info;
static SOS_BOOT_VIDEO_INFO boot_video;

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST) {

    EFI_STATUS status;
    /*
            FUTURE TASK
            Read config file and mode submition
    */
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    Print(L"Getting GOProtocol...");
    status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid,
                                              NULL, (VOID **)&GOP);
    CHECK(status);
    Print(L"Success\n");

    Print(L"Attempt to get better graphics setting...\n");
    UINTN info_size;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *gop_info = GOP->Mode->Info;
    UINT32 max_mode = GOP->Mode->MaxMode;
    Print(L"[Current] HR: %d VR: %d PF: %d PPSL: %d\n",
          gop_info->HorizontalResolution, gop_info->VerticalResolution,
          gop_info->PixelFormat, gop_info->PixelsPerScanLine);
    UINT32 target_mode = 0;
    for (int i = 0; i < max_mode; ++i) {
        status = GOP->QueryMode(GOP, i, &info_size, &gop_info);
        Print(L"Mode %d HR: %d VR: %d PF: %d PPSL: %d\n", i,
              gop_info->HorizontalResolution, gop_info->VerticalResolution,
              gop_info->PixelFormat, gop_info->PixelsPerScanLine);

        if (!EFI_ERROR(status) && gop_info->PixelFormat != PixelBltOnly &&
            gop_info->PixelFormat < PixelBitMask) // ignore BitMask for now
        {

            if (gop_info->HorizontalResolution == DEFAULT_HR &&
                gop_info->VerticalResolution == DEFAULT_VR) {
                target_mode = i;
                break;
            }
        }
    }
    // Apply video mode
    status = GOP->SetMode(GOP, target_mode);
    CHECK(status);
    Print(L"Success\n");
    // clear screen
    ST->ConOut->ClearScreen(ST->ConOut);

    Print(L"SillyOS Bootloader\n");
    Print(L"Version: Beta\n");

    Print(L"Loading kernel...");
    UINTN kmem_size = 0;
    UINTN kfile_size = 0;
    VOID *KERNEL = NULL;
    status = load_kernel(&KERNEL, &kmem_size, &kfile_size);
    CHECK(status);
    Print(L"=> Size of kernel file: %dBytes\n", kfile_size);
    Print(L"=> Size of kernel: %dBytes\n", kmem_size);
    KERNEL_ENTRY *KernelEntry = (KERNEL_ENTRY *)KERNEL;

    //	Getting ACPI tables
    Print(L"Fetching ACPI Tables...");
    EFI_CONFIGURATION_TABLE *CT = ST->ConfigurationTable;
    EFI_GUID Acpi20_guid = EFI_ACPI_20_TABLE_GUID;
    EFI_GUID Acpi10_guid = ACPI_10_TABLE_GUID;
    // EFI_GUID Smbios_guid = SMBIOS3_TABLE_GUID;
    UINT64 Acpi_signature =
        EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER_SIGNATURE;
    EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER *RSDP = NULL;
    UINT8 Acpi_version = 0;
    for (UINTN i = 0; i < ST->NumberOfTableEntries; i++) {
        // Print(L"%g\n", CT[i].VendorGuid);
        if (CompareGuid(&(CT[i].VendorGuid), &Acpi20_guid) == TRUE ||
            CompareGuid(&(CT[i].VendorGuid), &Acpi10_guid) == TRUE) {
            RSDP = (EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER
                        *)(CT[i].VendorTable);

            if (RSDP->Signature == Acpi_signature) { // RSDP found
                if (RSDP->Revision ==
                    EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION) { // Revsion matched
                    // Print(L"\nACPI version: 2\n");
                    Acpi_version =
                        EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION;
                    break;
                } else if (RSDP->Revision == 0) {
                    // Print(L"\nACPI version: 1\n");
                    Acpi_version = 1;
                    break;
                }
            }
        }
        RSDP = NULL;
        CT++; // next
    }
    // check table
    if (RSDP == NULL || Acpi_version == 0) {
        CHECK(EFI_NOT_FOUND);
    }
    Print(L"Success\n");

    //	Get memory map
    EFI_MEMORY_DESCRIPTOR *MemMap = (EFI_MEMORY_DESCRIPTOR *)0x1000;
    UINT64 MemMapSize = 0;
    UINT64 MapKey = 0;
    UINT64 DesSize = 0;
    UINT32 DesVersion = 0;
    // Get memory map
    Print(L"Getting memory map and terminating BootServices...\n");
    Print(L"Serial will be disconnected for now.\n");
    status = GetMemMap(&MapKey, &DesVersion, &DesSize, &MemMap, &MemMapSize);
    CHECK(status);
    // Do not put any calls between GetMemMap() and ExitBootServices()!
    for (int i = 0; i < 5; i++) {
        status = ST->BootServices->ExitBootServices(IH, MapKey);
        if (!EFI_ERROR(status)) {
            break;
        }
    }
    CHECK(status);

    /***	WARNING!	WARNING!	WARNING!	WARNING!	WARNING!
     * WARNI***/

    /***			DO	NOT	PUT	ANY	BOOT SERVICES	FUNCTION	BELOW
     * ***/
    /***	If we passed status check, then BootServices is no longer usable.
     * ***/

    /***	WARNING!	WARNING!	WARNING!	WARNING!	WARNING!	WAR
     * ***/

    // ST->RuntimeServices->SetVirtualAddressMap(MemMapSize, DesSize,
    // DesVersion, MemMap);  put all needed things into a structure
    boot_info.Magic = MAGIC;
    boot_info.Platform = PLATFORM_EFI;
    boot_info.Version = CONTENT_VERSION;

    // Kernel
    boot_info.KernelAddress = (VOID *)KernelEntry;
    boot_info.KernelSize = kmem_size;
    // Video
    boot_video.VerticalResolution = GOP->Mode->Info->VerticalResolution;
    boot_video.HorizontalResolution = GOP->Mode->Info->PixelsPerScanLine;
    boot_video.FrameBufferBase = GOP->Mode->FrameBufferBase;
    boot_video.FrameBufferSize = GOP->Mode->FrameBufferSize;
    boot_video.PixelSize = 4;

    // temporary
    boot_video.RIndex = 0;
    boot_video.GIndex = 1;
    boot_video.BIndex = 2;

    switch (GOP->Mode->Info->PixelFormat) {
    case PixelRedGreenBlueReserved8BitPerColor:
        boot_video.RIndex = 0;
        boot_video.GIndex = 1;
        boot_video.BIndex = 2;
        break;
    case PixelBlueGreenRedReserved8BitPerColor:
        boot_video.RIndex = 2;
        boot_video.GIndex = 1;
        boot_video.BIndex = 0;
        break;
        /*
case PixelBitMask:
        boot_info.PixelType = BITMASK;
        boot_info.Bitmask =
(UINT32)((UINT8)(gop_info->PixelInformation->RedMask) ; break;
        */
    default:
        break;
    }

    boot_video.Checksum =
        -(boot_video.VerticalResolution + boot_video.HorizontalResolution +
          boot_video.FrameBufferBase + boot_video.FrameBufferSize +
          boot_video.PixelSize + boot_video.RIndex + boot_video.GIndex +
          boot_video.BIndex);

    boot_info.VideoInfo = &boot_video;

    boot_info.MemoryMap = (VOID *)MemMap;
    boot_info.MemoryMapSize = MemMapSize;
    boot_info.DescriptorSize = DesSize;
    // ACPI Table
    boot_info.AcpiVersion = Acpi_version;
    boot_info.RSDP = (VOID *)RSDP;

    boot_info.RuntimeServices = (VOID *)(ST->RuntimeServices);

    // calculate ckecksum
    boot_info.Checksum =
        -(MAGIC + PLATFORM_EFI + CONTENT_VERSION +
          (UINT64)(boot_info.KernelAddress) + boot_info.KernelSize +
          (UINT64)(boot_info.VideoInfo) + (UINT64)(boot_info.MemoryMap) +
          boot_info.MemoryMapSize + boot_info.DescriptorSize +
          boot_info.AcpiVersion + (UINT64)(boot_info.RSDP) +
          (UINT64)(boot_info.RuntimeServices));

    // See you in Kernel :)
    KernelEntry(&boot_info);

    return EFI_SUCCESS; // We'll never go here, but we must make compiler happy
                        // ;)
}

EFI_STATUS GetMemMap(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize,
                     EFI_MEMORY_DESCRIPTOR **Memmap, UINT64 *MemmapSize) {
    // lazy..
    EFI_STATUS status;
    UINT64 Size = 0;
    UINT64 Pages = 1;
    // Get Memory Map Size frist
    while (1) {
        status = gBS->AllocatePages(AllocateAnyPages, EfiLoaderData, Pages,
                                    (UINT64 *)*Memmap);
        if (status != EFI_SUCCESS) {
            return status;
        }
        Size = Pages * 4096;
        status = gST->BootServices->GetMemoryMap(&Size, *Memmap, Key, DesSize,
                                                 DesVersion);
        if (status == EFI_BUFFER_TOO_SMALL) {
            Pages++;
        } else if (status == EFI_SUCCESS) {
            *MemmapSize = Size;
            return status;
        } else {
            return status;
        }
    }
    return EFI_SUCCESS;
}

