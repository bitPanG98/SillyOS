#include <Compiler.h>
#include <Booting.h>
#include <Graphics.h>
#include <UI.h>
#include <CPU.h>
#include <Peripheral.h>
#include <Interrupt.h>
#include <ACPI.h>

extern "C" void PlatformMain(SOS_BOOT_INFO *boot_info)
{
    //Initialize serial
    Peripheral::Serial::Initialize(Peripheral::Serial::SERIAL_PORTA);
    Peripheral::Serial::Write("\n3==============================D\n");
    Peripheral::Serial::Write(" SillyOS Kernel Debugging Port\n");
    Peripheral::Serial::Write("3==============================D\n");

    //Initialize graphics (Frame Buffer, EDID...)
    Graphics::Initialize(boot_info->VideoInfo);
    Graphics::Clear(0xffffff);
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

    //Initialize ACPI
    ACPI::Initialize(boot_info->RSDP);
    //ACPI OK msg
    LOG("[");
    UI::Terminal::SetColor(0xf4f141);
    LOG("ACPI");
    UI::Terminal::SetColor(DEFAULT_TEXT_COLOR);
    LOG("] => ");
    UI::Terminal::SetColor(0x42f486);
    LOG("OK\n");
    UI::Terminal::SetColor(DEFAULT_TEXT_COLOR);

    //Memory::Initialize();


    //Interrupt::Initialize();
    //Early memory allocation
    //Initialize memory management
    //End early memory allocation
    //Initialize interrupt

    //Compile information
    //Build Unified System Call Interface (Register system call interrupt, support POSIX)
    //IDK

    while (true);
}
