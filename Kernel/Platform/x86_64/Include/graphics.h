#pragma once
#include <boot.h>
#include <types.h>

#define DEFAULT_COLOR 0x252525

namespace Graphics {
/*  graphics.c    */
void init(SOS_BOOT_VIDEO_INFO *);
void plot(u32, u32, u32);
void clear_screen();
void clear_screen(u32);
u32 get_width();
u32 get_height();
}


namespace Graphics::Terminal {
/*  terminal.c   */
void printf(char *, ...);
void put_char(char, u32);
void set_pos(u32, u32);
void set_color(u32);
}

