#include <compiler.h>
#include <boot.h>
#include <graphics.h>
#include <ui.h>
#include <cpu.h>
#include <peripheral.h>

extern "C" void kernel_init(SOS_BOOT_INFO *boot_info)
{
    //Initialize serial
    Peripheral::Serial::init(Peripheral::Serial::SERIAL_PORTA);
    Peripheral::Serial::write("3======================D\n");
    Peripheral::Serial::write(" SillyOS Debugging Port\n");
    Peripheral::Serial::write("3======================D\n");

    //Initialize graphics (Frame Buffer, EDID...)
    Graphics::init(boot_info->VideoInfo);
    // 'self comment' code
    UI::Terminal::init();
    UI::Logging::log("[Graphics] => OK\n");

    //Initialize GDT
    CPU::GDT::init();
    UI::Logging::log("[GDT] => OK\n");
    //Early memory allocation (Basic malloc, free)
    //Initialize memory management
    //End early memory allocation
    //Initialize interrupt

    //Compile information
    //Build Unified System Call Interface (Register system call interrupt, support POSIX)
    //IDK

    while (true);
}
