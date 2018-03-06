#include <graphics.h>

u32 Red(u32);
u32 Green(u32);
u32 Blue(u32);

static struct {
    u8 *_frame_buff;
    u64 _buffer_size;
    u32 _maxX;
    u32 _maxY;
    u8 _pixel_size;
    u8 _red_index;
    u8 _green_index;
    u8 _blue_index;
} video_info;

void graphics_init(SOS_BOOT_VIDEO_INFO *info) {
    video_info._frame_buff = (u8 *)info->FrameBufferBase;
    video_info._buffer_size = info->FrameBufferSize;
    video_info._maxX = info->HorizontalResolution;
    video_info._maxY = info->VerticalResolution;
    video_info._pixel_size = info->PixelSize;
    video_info._red_index = info->RIndex;
    video_info._green_index = info->GIndex;
    video_info._blue_index = info->BIndex;
}

void plot(u32 x, u32 y, u32 color) {
    u64 pos = (y * video_info._maxX + x) * video_info._pixel_size;
    video_info._frame_buff[pos + video_info._red_index] = Red(color);
    video_info._frame_buff[pos + video_info._green_index] = Green(color);
    video_info._frame_buff[pos + video_info._blue_index] = Blue(color);
}

void clear_screen(u32 color) {
    for (u32 i = 0; i < video_info._buffer_size; i += video_info._pixel_size) {
        video_info._frame_buff[i + video_info._red_index] = Red(color);
        video_info._frame_buff[i + video_info._green_index] = Green(color);
        video_info._frame_buff[i + video_info._blue_index] = Blue(color);
    }
}

u32 Red(u32 color) { return (color & 0xff0000) >> 16; }
u32 Green(u32 color) { return (color & 0xff00) >> 8; }
u32 Blue(u32 color) { return (color & 0xff); }
