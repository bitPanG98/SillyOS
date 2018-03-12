#include <peripheral.h>
#include <cpu.h>

namespace Peripheral::Serial {
    static u16 _port = 0;
    void init(u16 port){
        _port = port;
        CPU::IO::outb(_port + 1, 0);
        CPU::IO::outb(_port + 3, 0x80);
        CPU::IO::outb(_port + 0, 0x3);
        CPU::IO::outb(_port + 1, 0);
        CPU::IO::outb(_port + 3, 0x3);
        CPU::IO::outb(_port + 2, 0xc7);
        CPU::IO::outb(_port + 4, 0xb);
    }

    void write(char *str){
        while(*str != '\0'){
            put(*str);
            str++;
        }
    }

    void put(char in){
        while((CPU::IO::inb(_port + 5) & 0x20) == 0);
        CPU::IO::outb(_port, in);
    }
}