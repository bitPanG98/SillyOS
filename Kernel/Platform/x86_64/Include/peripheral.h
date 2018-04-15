#pragma once
#include <types.h>

namespace Peripheral::Serial {
    const u16 SERIAL_PORTA = 0x3f8;
    const u16 SERIAL_PORTB = 0x2f8;
    const u16 SERIAL_PORTC = 0x3e8;
    const u16 SERIAL_PORTD = 0x2e8;

    void Initialize(u16);
    void Write(char);
    void Write(char *);
}