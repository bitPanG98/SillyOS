#include <ACPI.h>
#include <UI.h>
#include <String.h>

using namespace ACPI::Tables;

namespace ACPI {
    static ACPI_RSDP *rsdp;
    u64 CalculateChecksum(u8* ptr, u32 n);

    void Initialize(void *rsdp_ptr){
        ACPI_RSDP *unsafe_rsdp = (ACPI_RSDP *)rsdp_ptr;
        //if signature isn't 'RSD PTR\0'
        if(!CmpMemory((void *)&(unsafe_rsdp->Signature), (void *)ACPI_RSDP_SIGNATURE, 8)){
            PANIC("[ACPI] => Invalid RSDP signature!\n");
        }
        /*  
            To calculate the checksum of RSDP
            we sum up every bytes in the structure
            and check wherether lowest byte is equal 0
            zero: valid, non-zero: invalid
        */
       //TODO: check revision before checksum
        u32 checksum = CalculateChecksum((u8 *)unsafe_rsdp, unsafe_rsdp->Length);
        //if the lowest byte isn't zero
        if(checksum & 0xff){
            PANIC("[ACPI] => Invalid RSDP checksum!\n");
        }

        //RSDP is good to go
        rsdp = unsafe_rsdp;

        //TODO: CHECK XSDT and RSDT(dunno do we really need to implement it)

    }   

    //TODO: MOVE THIS FUNCTION TO SillyLib(maybe?)
    u64 CalculateChecksum(u8* ptr, u32 n){
        u64 sum = 0;
        for(u32 i = 0; i < n; i++){
            sum += ptr[i];
        }
        return sum;
    }

}