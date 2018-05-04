#include <ACPI.h>
#include <UI.h>
#include <String.h>

using namespace ACPI::Tables;

namespace ACPI {
    static ACPI_RSDP *rsdp;


    void Initialize(void *RSDP){
        rsdp = (ACPI_RSDP *)RSDP;
        /*  Verify  */
        if(!CmpMemory((void *)&(rsdp->Signature), (void *)ACPI_RSDP_SIGNATURE, 8)){
            PANIC("[ACPI] => Invalid signature!\n");
        }
        /*  Checksum!
            Since ACPI 2.0, RSDP structure seprated in 2 part
            the original one which carried the RSDT and 
            the extended one that carried XSDT,
            so we have to do checksum of each part.
        */
       //   ACPI 1.0 part
        u32 checksum = 0;
        for(u32 i = 0; i < rsdp->Length; i++){
            checksum += ((u8 *)rsdp)[i];
        }
        //if not sum to zero
        if(!checksum){
            PANIC("[ACPI] => ACPI 1.0 checksum failed!\n");
        }
        //  ACPI 2.0 part
        u8 *extended_rsdp = (u8 *)(rsdp + rsdp->Length);
        while(extended_rsdp != (u8 *)(rsdp + sizeof(ACPI_RSDP))){

        }
    }

}