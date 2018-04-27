#include "Main.h"

EFI_STATUS convert_memmap(SOS_MEM_INFO **sysmap, UINT32 *des_size, UINT32 *map_size)
{
    EFI_STATUS status;
    
    EFI_MEMORY_DESCRIPTOR *efimap = (EFI_MEMORY_DESCRIPTOR *)NULL;
    UINT64 efimap_size = 0;
    UINT64 key = 0;
    UINT64 efides_size = 0;
    UINT32 version = 0;
    //get memory map
    status = GetMemMap(&_key, &_version, &efides_size, &efimap, &efimap_size);
    if(EFI_ERROR(status)){
        return status;
    }

    /*
        if current sys map size > allocated size then{
            pagesize++
            allocate pages with pagesize
            copy data from old buffer to new one
            release old buffer
        }
        keep building sysmap{
            while not finish{

            }
            break
        }
    */
    UINT32 _map_size = 1; //start from 1 page
    status = gBS->AllocatePages(AllocatePages, EfiLoaderCode, _map_size, *sysmap);
    if(EFI_ERROR(status)){
        return status;
    }
    *des_size = sizeof(SOS_MEM_INFO);
    UINT8 *ptr = (UINT8 *)efimap;
    while(ptr < (UINT8 *)efimap + efimap_size){
        //add size
        *map_size += *des_size;
        if(*map_size > _map_size * 4096){
            //need more space
            _map_size++;
            VOID *temp_buff = NULL;
            status = gBS->AllocatePages(AllocatePages, EfiLoaderCode, _map_size, temp_buff);
            if(EFI_ERROR(status)){
                *sysmap = NULL;
                return status;
            }
            CopyMem(temp_buff, *sysmap, *map_size - *des_size);
            gBS->FreePages(*sysmap, _map_size);
            *sysmap = temp_buff;
        }
        //NDY
        *sysmap->PhyStart = (EFI_MEMORY_DESCRIPTOR *)ptr->Phy;

        switch((EFI_MEMORY_DESCRIPTOR *)ptr->Type){
            case EfiReservedMemoryType:{
                *sysmap->Type = SOS_MEM_TYPE_UNUSABLE;
                break;
            }
            case EfiLoaderCode:{
                *sysmap->Type = SOS_MEM_TYPE_KERNAL;
                break;
            }
            case EfiLoaderData:{
                *sysmap->Type = SOS_MEM_TYPE_KERNEL;
                break;
            }
            //this two are same shit
            case EfiBootServicesCode:
            case EfiBootServicesData:{
                *sysmap->Type = SOS_MEM_TYPE_FREE;
                break;
            }
            case EfiRuntimeServicesCode:
            case EfiRuntimeServicesData:{
                *sysmap->Type = SOS_MEM_TYPE_KERNEL;
                break;
            }
            case EfiConventionalMemory:{
                *sysmap->Type = SOS_MEM_TYPE_FREE;
                break;
            }
            case EfiUnusableMemory:{
                *sysmap->Type = SOS_MEM_TYPE_UNUSABLE;
                break;
            }
            case EfiACPIReclaimMemory:{
                *sysmap->Type = SOS_MEM_TYPE_ACPI;
                break;
            }
            case EfiACPIMemoryNVS:{
                *sysmap->Type = SOS_MEM_TYPE_ACPI;
                break;
            }
            case EfiMemoryMappedIO:{
                *sysmap->Type = SOS_MEM_TYPE_IO;
                break;
            }
            case EfiMemoryMappedIOPortSpace:{
                *sysmap->Type = SOS_MEM_TYPE_IO;
                break;
            }
            case EfiPalCode:{
                *sysmap->Type = SOS_MEM_TYPE_UNUSABLE;
                break;
            }
            case EfiPersistentMemory:{
                *sysmap->Type = SOS_MEM_TYPE_UNUSABLE;
                break;
            }
            case EfiMaxMemoryType:{
                *sysmap->Type = SOS_MEM_TYPE_UNUSABLE;
                break;
            }
            default:{
                //treat it as unusable memory
                *sysmap->Type = SOS_MEM_TYPE_UNUSABLE;
                break;
            }
        }
        *sysmap++; //next entry
        ptr += DesSize;
    }
}