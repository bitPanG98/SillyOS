#include "main.h"

EFI_STATUS load_kernel(VOID **kernel, UINTN *kernel_size, UINTN *file_size) {
    EFI_STATUS status;
    /*
        STEP 1: Get kernel's file protocol
    */
    VOID *kernel_file = NULL;
    Print(L"\n=> Loading %s from drive...", KERNEL_FILE);
    status = LoadFileFromTheDrive(KERNEL_FILE, &kernel_file, file_size);
    if(EFI_ERROR(status)){
        return status;
    }
    /*
        STEP 2: Validate kernel
    */
    Print(L"\n=> Validate kernel...");
    Elf64_Ehdr elf_header;
    CopyMem(&(elf_header), kernel_file, sizeof(Elf64_Ehdr));
    if(!is_ELF(elf_header)){
        Print(L"Not a valid ELF file!\n");
        return EFI_INVALID_PARAMETER;
    }
    Print(L"\n");
    UINT8 *pheader_ptr = (UINT8 *)(kernel_file + elf_header.e_phoff);
    for (UINTN i = 0; i < elf_header.e_phnum; i++){
        Elf64_Phdr *p_head = (Elf64_Phdr *)pheader_ptr;
        if(p_head->p_type == PT_LOAD){
            VOID *file_offset = (VOID *)(kernel_file + p_head->p_offset);
            VOID *mem_offset = (VOID *)p_head->p_vaddr;
            CopyMem(mem_offset, file_offset, p_head->p_filesz);
            *kernel_size += p_head->p_filesz;
        }
        pheader_ptr += elf_header.e_phentsize;
    }
    *kernel = (VOID *)elf_header.e_entry;
    gBS->FreePool(kernel_file);
    return EFI_SUCCESS;
}

UINT8 is_ELF(Elf64_Ehdr elf_header) {
    UINT8 ELF_magic[] = {0x7f, 0x45, 0x4c, 0x46}; // 0x7f, 'E', 'L', 'F'
    if (CompareMem(&elf_header, &ELF_magic[0], sizeof(ELF_magic)) != 0) {
        return 0;
    }
    return 1;
}

EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data,
                                OUT UINTN *Size) {

    EFI_STATUS status;
    EFI_HANDLE *handles = NULL;
    EFI_FILE *root = NULL;
    EFI_FILE *file = NULL;
    EFI_FILE_INFO *info = NULL;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFS = NULL;
    UINTN MaxHandles;
    UINTN InfoBuffSize = 0;

    status =
        gBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleFileSystemProtocolGuid,
                                NULL, &MaxHandles, &handles);
    if (EFI_ERROR(status)) {
        // Print(L"\n1\n");
        return status;
    }
    for (UINTN i = 0; i < MaxHandles; i++) {
        status = gBS->HandleProtocol(
            handles[i], &gEfiSimpleFileSystemProtocolGuid, (void **)&SFS);
        if (EFI_ERROR(status)) {
            // Print(L"\n2\n");
            return status;
        }
        status = SFS->OpenVolume(SFS, &root);
        if (EFI_ERROR(status)) {
            // Print(L"\n3\n");
            return status;
        }
        // check is needed file exist?
        status = root->Open(root, &file, FileName, EFI_FILE_MODE_READ, 0);
        if (status == EFI_SUCCESS) {
            // found!
            break;
        }
    }

    // Release
    gBS->FreePool(handles);

    // still nothing...
    if (file == NULL) {
        return status;
    }

    // Get what size of buffer it need.
    status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, NULL);
    if (status == EFI_BUFFER_TOO_SMALL) {
        // Need more space!
        status = gBS->AllocatePool(EfiBootServicesData, InfoBuffSize,
                                   (VOID **)&info);
        if (EFI_ERROR(status)) {
            // Print(L"\n4\n");
            return status;
        }
    } else if (EFI_ERROR(status)) {
        // Print(L"\n5\n");
        return status;
    }

    // if go here, mean sucess to allocate pool.
    // do the real getinfo().
    status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, info);
    if (EFI_ERROR(status)) {
        // Print(L"\n6\n");
        return status;
    }
    *Size = info->FileSize;
    gBS->FreePool(info);

    status = gBS->AllocatePool(EfiLoaderData, *Size, Data);
    if (EFI_ERROR(status)) {
        // Print(L"\n7\n");
        return status;
    }

    // Read file
    status = file->Read(file, Size, (UINT8 *)*Data);
    if (EFI_ERROR(status)) {
        // Print(L"\n8\n");
        return status;
    }

    // Finish!
    status = file->Close(file);
    if (EFI_ERROR(status)) {
        // Print(L"\n9\n");
        return status;
    }
    root->Close(root);

    return EFI_SUCCESS;
}
