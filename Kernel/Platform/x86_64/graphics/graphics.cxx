#include <graphics.h>

namespace Graphics{

u32 Red(u32);
u32 Green(u32);
u32 Blue(u32);

static struct {
    u8 *frame_buff;
    u64 buffer_size;
    u32 width; //unit: pixel
    u32 height; //unit: pixel
    u8 pixel_size;
    u8 red_index;
    u8 green_index;
    u8 blue_index;
} video_info;

void init(SOS_BOOT_VIDEO_INFO *info) {
    video_info.frame_buff = (u8 *)info->FrameBufferBase;
    video_info.buffer_size = info->FrameBufferSize;
    video_info.width = info->HorizontalResolution;
    video_info.height = info->VerticalResolution;
    video_info.pixel_size = info->PixelSize;
    video_info.red_index = info->RIndex;
    video_info.green_index = info->GIndex;
    video_info.blue_index = info->BIndex;
}

void plot(u32 x, u32 y, u32 color) {
    u64 pos = (y * video_info.width + x) * video_info.pixel_size;
    video_info.frame_buff[pos + video_info.red_index] = Red(color);
    video_info.frame_buff[pos + video_info.green_index] = Green(color);
    video_info.frame_buff[pos + video_info.blue_index] = Blue(color);
}

void clear_screen(u32 color) {
    for (u32 i = 0; i < video_info.buffer_size; i += video_info.pixel_size) {
        video_info.frame_buff[i + video_info.red_index] = Red(color);
        video_info.frame_buff[i + video_info.green_index] = Green(color);
        video_info.frame_buff[i + video_info.blue_index] = Blue(color);
    }
}

u32 get_width(){
    return video_info.width;
}

u32 get_height(){
    return video_info.height;
}

u32 Red(u32 color) { return (color & 0xff0000) >> 16; }
u32 Green(u32 color) { return (color & 0xff00) >> 8; }
u32 Blue(u32 color) { return (color & 0xff); }
}