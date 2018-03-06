#ifndef _GRAPHICS_GRAPHICS_H_
#define _GRAPHICS_GRAPHICS_H_
#include <boot.h>
#include <types.h>

#define DEFAULT_COLOR 0x252525
/*  graphics.c    */
void graphics_init(SOS_BOOT_VIDEO_INFO *);
void plot(u32, u32, u32);
void clear_screen(u32);

/*  video.c   */
void put_char(char, u32);
bool is_char(char);
bool is_num(char);
bool is_capital(char);
bool is_low(char);

#endif
