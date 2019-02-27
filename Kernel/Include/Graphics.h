#pragma once
#include <Booting.h>
#include <Types.h>

namespace Graphics {
struct VideoInfo{
    u8 *frame_buff;
    u64 buffer_size;
    u32 width; //unit: pixel
    u32 height; //unit: pixel
    u8 pixel_size;
    u8 red_index;
    u8 green_index;
    u8 blue_index;
};

/*  graphics.c    */
u32 Red(u32);
u32 Green(u32);
u32 Blue(u32);
void Initialize(SOS_BOOT_VIDEO_INFO *);
void Plot(u32, u32, u32);
void Clear();
void Clear(u32);
u32 GetWidth();
u32 GetHeight();
}

