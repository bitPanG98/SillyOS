#pragma once
#include <boot.h>
#include <types.h>

namespace Graphics {
/*  graphics.c    */
void init(SOS_BOOT_VIDEO_INFO *);
void plot(u32, u32, u32);
void clear_screen();
void clear_screen(u32);
u32 get_width();
u32 get_height();
}

