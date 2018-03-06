#include <checking.h>
#include <boot.h>
#include <graphics.h>

extern "C" void kernel_init(SOS_BOOT_INFO *boot_info) {

    SOS_BOOT_VIDEO_INFO *video_info = boot_info->VideoInfo;

    graphics_init(video_info);

    clear_screen(DEFAULT_COLOR);

    put_char('_', 0xffffff);

    while (true);
}
