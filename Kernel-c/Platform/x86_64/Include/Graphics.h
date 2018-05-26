#pragma once
#include <Booting.h>
#include <Types.h>

namespace Graphics {
/*  graphics.c    */
void Initialize(SOS_BOOT_VIDEO_INFO *);
void Plot(u32, u32, u32);
void Clear();
void Clear(u32);
u32 GetWidth();
u32 GetHeight();
}

