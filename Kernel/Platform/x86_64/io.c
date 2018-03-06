#include <io.h>

extern "C" u8 _inb(u16 port);
extern "C" u16 _inw(u16 port);
extern "C" u32 _indw(u16 port);

extern "C" void _outb(u16 port, u8 data);
extern "C" void _outw(u16 port, u16 data);
extern "C" void _outdw(u16 port, u32 data);

/*
    Input instructions
*/
u8 inb(u16 port) { return _inb(port); }

u16 inw(u16 port) { return _inw(port); }

u32 indw(u16 port) { return _indw(port); }
/*
    Output instructions
*/
void outb(u16 port, u8 data) { _outb(port, data); }

void outw(u16 port, u16 data) { _outw(port, data); }

void outdw(u16 port, u32 data) { _outdw(port, data); }