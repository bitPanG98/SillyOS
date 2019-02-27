#include <CPU.h>
#include <UI.h>
/*
    Global Descriptor Table or GDT,
    Are basiclly useless in Flat Mode.
    But it still needed for IDT, We can
    just use the selector which stored in cs,
    but thats is not a good idea, since we dont actually
    know where the GDT sit on, it may causing problems when
    we accidently overrided it.

    So...we have to make one @_@

*/
namespace CPU::GDT {

    //null, Ring0 Code, Ring0 data
    const u16 GDT_ENTRIES_NUMBER = 3;
    //True global variable
    GDT_PTR gdt_ptr;
    GDT_ENTRY gdt[GDT_ENTRIES_NUMBER];

    void Initialize(){
        /*
            null is nothing
        */
        gdt[0].LimitLow = 0;
        gdt[0].BaseLow = 0;
        gdt[0].BaseMid = 0;
        gdt[0].Access = 0;
        gdt[0].Flags = 0;
        gdt[0].BaseHigh = 0;

        /*
            code is meaningless but it can do a lot
        */
        gdt[1].LimitLow = 0xffff;
        gdt[1].BaseLow = 0;
        gdt[1].BaseMid = 0;
        gdt[1].Access = 0x9a;
        gdt[1].Flags = 0xaf;
        gdt[1].BaseHigh = 0;

        /*
            data is meaningful but cannot be understood without processing.
        */
        gdt[2].LimitLow = 0xffff;
        gdt[2].BaseLow = 0;
        gdt[2].BaseMid = 0;
        gdt[2].Access = 0x92;
        gdt[2].Flags = 0xaf;
        gdt[2].BaseHigh = 0;

        gdt_ptr.Limit = sizeof(gdt)-1;
        gdt_ptr.Base = (u64)&gdt[0];
        ApplyGDT(&gdt_ptr, 0x8, 0x10);
    }

    void ApplyGDT(GDT_PTR *ptr, u16 code, u16 data){
        asm volatile("lgdt (%0)"::"r"(ptr));
        FlushGDT(code, data);
    }

    void ReadGDT(GDT_PTR *ptr){
        asm("sgdt (%0)"::"r"(ptr));
    }

}