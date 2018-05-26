#include <Interrupt.h>
#include <CPU.h>
#include <UI.h>
#include <String.h>

using namespace CPU::CPUID;
namespace Interrupt {
inline void EnableInterrupt() { asm("cli"); }
inline void DisableInterrupt() { asm("sti"); }

IDT_ENTRY idt[256];

void Initialize(){
    //Zero out the table
    SetMemory((void *)idt, 0x0, 256);

    //Check is APIC available
    u32 regs[4];
    CPUID(0x1, &regs[0], &regs[1], &regs[2], &regs[3]);
    if(regs[3] & F1_EDX_APIC){
        //APIC available
        LOG("APIC available\n");
        //Initialize APIC
    }else{
        //APIC not available, legacy PIC instead?
        PANIC("APIC not available on this machine.");
    }
}

}
