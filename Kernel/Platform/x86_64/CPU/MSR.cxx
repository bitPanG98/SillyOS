#include <cpu.h>

namespace CPU::MSR{

    bool IsAvailable(){
        u32 regs[4];
        CPUID::CPUID(0x1, &regs[0], &regs[1], &regs[2], &regs[3]);
        return regs[3] & F1_EDX_MSR ? true : false;
    }

    void ReadMSR(u32 addr, u32 *high, u32 *low){
        asm()
    }
    void WriteMSR(u32 addr, u32 high, u32 low){

    }

}