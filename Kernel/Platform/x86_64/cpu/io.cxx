#include <cpu.h>

namespace CPU::IO {
    extern "C" u8 _inb(u16 port);
    extern "C" u16 _inw(u16 port);
    extern "C" u32 _indw(u16 port);

    extern "C" void _outb(u16 port, u8 data);
    extern "C" void _outw(u16 port, u16 data);
    extern "C" void _outdw(u16 port, u32 data);

    u8 inb(u16 port){
        _inb(port);
    }

    u16 inw(u16 port){
        _inw(port);
    }

    u32 indw(u16 port){
        _indw(port);
    }

    void outb(u16 port, u8 data){
        _outb(port, data);
    }

    void outw(u16 port, u16 data){
        _outw(port, data);
    }

    void outdw(u16 port, u32 data){
        outdw(port, data);
    }

}