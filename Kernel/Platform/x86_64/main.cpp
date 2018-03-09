#include <compiler.h>
#include <boot.h>
#include <graphics.h>

using namespace Graphics;

extern "C" void kernel_init(SOS_BOOT_INFO *boot_info) {
    // Initialize graphics settings
    init(boot_info->VideoInfo);
    // 'self comment' code
    clear_screen();
    // print our silly name
    Terminal::set_color(0xff0000);
    Terminal::printf("Silly");
    Terminal::set_color(0xffffff);
    Terminal::printf("OS\n");

    Terminal::printf("test integer: %i\n", (i64)123456);
    Terminal::printf("test neg-integer: %d\n", (i64)-123456);
    Terminal::printf("test lower hex: 0x%x\n", 0x1234abcde);
    Terminal::printf("test upper integer: 0x%X\n", 0x1234abcde);
    Terminal::printf("test binary: %b\n", (u64)4);
    Terminal::printf("test string: %s\n", "Ayy!");
    for(int i = 0; i < 255; i++){
        Terminal::printf("O");
    }
    while (true);
}
