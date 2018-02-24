#include <types.hpp>
#include <boot.hpp>

extern "C" void kernel_init(SOS_BOOT_INFO *boot_info){
    SOS_BOOT_VIDEO_INFO *video_info = boot_info->VideoInfo;
    u8 *frame_buff = (u8 *)video_info->FrameBufferBase;
    u32 maxX  = video_info->HorizontalResolution;
    for (u32 i = 0; i < maxX; i+=4){
        frame_buff[i] = 0xff;
        frame_buff[i+1] = 0xff;
        frame_buff[i+2] = 0xff;

    }

}