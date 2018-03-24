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
    //Graphics OK msg
    UI::Logging::log("[");
    UI::Terminal::set_color(0xf4f141);
    UI::Logging::log("Graphics");
    UI::Terminal::set_color(DEFAULT_TEXT_COLOR);
    UI::Logging::log("] => ");
    UI::Terminal::set_color(0x42f486);
    UI::Logging::log("OK\n");
    UI::Terminal::set_color(DEFAULT_TEXT_COLOR);

    //Initialize GDT
    CPU::GDT::init();
    CPU::GDT::print();
    //GDT OK msg
    UI::Logging::log("[");
    UI::Terminal::set_color(0xf4f141);
    UI::Logging::log("GDT");
    UI::Terminal::set_color(DEFAULT_TEXT_COLOR);
    UI::Logging::log("] => ");
    UI::Terminal::set_color(0x42f486);
    UI::Logging::log("OK\n");
    UI::Terminal::set_color(DEFAULT_TEXT_COLOR);
    //Early memory allocation (Basic malloc, free)
    //Initialize memory management
    //End early memory allocation
    //Initialize interrupt

    //Compile information
    //Build Unified System Call Interface (Register system call interrupt, support POSIX)
    //IDK

    while (true);
}
