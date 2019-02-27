#include <Graphics.h>

namespace Graphics{

static struct VideoInfo video_info;

void Initialize(SOS_BOOT_VIDEO_INFO *info) {
    video_info.frame_buff = (u8 *)info->FrameBufferBase;
    video_info.buffer_size = info->FrameBufferSize;
    video_info.width = info->HorizontalResolution;
    video_info.height = info->VerticalResolution;
    video_info.pixel_size = info->PixelSize;
    video_info.red_index = info->RIndex;
    video_info.green_index = info->GIndex;
    video_info.blue_index = info->BIndex;
}

void Plot(u32 x, u32 y, u32 color) {
    u64 pos = (y * video_info.width + x) * video_info.pixel_size;
    video_info.frame_buff[pos + video_info.red_index] = Red(color);
    video_info.frame_buff[pos + video_info.green_index] = Green(color);
    video_info.frame_buff[pos + video_info.blue_index] = Blue(color);
}

void Clear(u32 color) {
    for (u32 i = 0; i < video_info.buffer_size; i += video_info.pixel_size) {
        video_info.frame_buff[i + video_info.red_index] = Red(color);
        video_info.frame_buff[i + video_info.green_index] = Green(color);
        video_info.frame_buff[i + video_info.blue_index] = Blue(color);
    }
}

u32 GetWidth(){
    return video_info.width;
}

u32 GetHeight(){
    return video_info.height;
}

u32 Red(u32 color) { return (color & 0xff0000) >> 16; }
u32 Green(u32 color) { return (color & 0xff00) >> 8; }
u32 Blue(u32 color) { return (color & 0xff); }
}