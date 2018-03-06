#ifndef _IO_H_
#define _IO_H_
#include <types.h>

u8 inb(u16 port);
u16 inw(u16 port);
u32 indw(u16 port);

void outb(u16 port, u8 data);
void outw(u16 port, u16 data);
void outdw(u16 port, u32 data);

#endif