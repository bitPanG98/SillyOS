#include <compiler.h>
#include <boot.h>
#include <graphics.h>
#include <ui.h>
#include <cpu.h>
#include <peripheral.h>
#include <string.h>

extern "C" void PlatformMain(SOS_BOOT_INFO *boot_info)
{
    //Initialize serial
    Peripheral::Serial::Initialize(Peripheral::Serial::SERIAL_PORTA);
    Peripheral::Serial::Write("\n3==============================D\n");
    Peripheral::Serial::Write(" SillyOS Kernel Debugging Port\n");
    Peripheral::Serial::Write("3==============================D\n");

    //Initialize graphics (Frame Buffer, EDID...)
    Graphics::Initialize(boot_info->VideoInfo);
    // 'self comment' code
    UI::Terminal::Initialize();
    //Graphics OK msg
    LOG("[");
    UI::Terminal::SetColor(0xf4f141);
    LOG("Graphics");
    UI::Terminal::SetColor(DEFAULT_TEXT_COLOR);
    LOG("] => ");
    UI::Terminal::SetColor(0x42f486);
    LOG("OK\n");
    UI::Terminal::SetColor(DEFAULT_TEXT_COLOR);

    //Initialize GDT
    CPU::GDT::Initialize();
    //GDT OK msg
    LOG("[");
    UI::Terminal::SetColor(0xf4f141);
    LOG("GDT");
    UI::Terminal::SetColor(DEFAULT_TEXT_COLOR);
    LOG("] => ");
    UI::Terminal::SetColor(0x42f486);
    LOG("OK\n");
    UI::Terminal::SetColor(DEFAULT_TEXT_COLOR);
    
    //Early memory allocation (Basic malloc, free)
    //Initialize memory management
    //End early memory allocation
    //Initialize interrupt

    //Compile information
    //Build Unified System Call Interface (Register system call interrupt, support POSIX)
    //IDK

    while (true);
}
