#include <cpu.h>
#include <ui.h>
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
    extern "C" void flush(u16 code, u16 data);

    //null, Ring0 Code, Ring0 data
    const u16 GDT_ENTRIES_NUMBER = 3;
    //True global variable
    GDT_PTR gdt_ptr;
    GDT_ENTRY gdt[GDT_ENTRIES_NUMBER];

    void init(){
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
        


        write(&gdt_ptr, 0x8, 0x10);
    }

    void write(GDT_PTR *ptr, u16 code, u16 data){
        asm volatile("lgdt (%0)"::"r"(ptr));
        flush(code, data);
    }

    void read(GDT_PTR *ptr){
        asm("sgdt (%0)"::"r"(ptr));
    }

/*
    BUGGY
*/
    // void print(){
    //     GDT_PTR ptr;
    //     read(&ptr);
    //     UI::Logging::log("PTR ADDR: 0x%x\n", ptr.Base);
    //     u16 size = ptr.Limit / sizeof(GDT_ENTRY) + 1;
    //     GDT_ENTRY *temp_gdt = (GDT_ENTRY *)ptr.Base;
    //     UI::Logging::log("num. of GDT: %i\n", size);
    //     for(u16 i = 0; i < size; i++){
    //         UI::Logging::log("0x%x: LL:0x%x BL:0x%x BM:%x Access:%b LM:0x%x Flags:%b BH:0x%x\n", i*8, temp_gdt->LimitLow, temp_gdt->BaseLow, temp_gdt->BaseMid, temp_gdt->Access, temp_gdt->Flags, temp_gdt->BaseHigh);
    //         temp_gdt++;
    //     }

    // }
}