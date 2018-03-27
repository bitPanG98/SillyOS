#include <compiler.h>
#include <boot.h>
#include <graphics.h>
#include <ui.h>
#include <cpu.h>
#include <peripheral.h>
#include <string.h>

extern "C" void kernel_init(SOS_BOOT_INFO *boot_info)
{
    //Initialize serial
    Peripheral::Serial::init(Peripheral::Serial::SERIAL_PORTA);
    Peripheral::Serial::write("\n3==============================D\n");
    Peripheral::Serial::write(" SillyOS Kernel Debugging Port\n");
    Peripheral::Serial::write("3==============================D\n");

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
    //GDT OK msg
    UI::Logging::log("[");
    UI::Terminal::set_color(0xf4f141);
    UI::Logging::log("GDT");
    UI::Terminal::set_color(DEFAULT_TEXT_COLOR);
    UI::Logging::log("] => ");
    UI::Terminal::set_color(0x42f486);
    UI::Logging::log("OK\n");
    UI::Terminal::set_color(DEFAULT_TEXT_COLOR);

    UI::Logging::log("Formatting test.\n");
    char buff[255];
    i64 A = -123456789;
    u64 B = 0x1234ABCDEF;
    char *C = "Aim high fly high?\nNope.";
    u16 D = 0x1234;
    UI::Logging::log("i64 A = -123456789;\n");
    UI::Logging::log("u64 B = 0x1234ABCDEF;\n");
    UI::Logging::log("char *C = \"Aim high fly high?\\nNope.\";\n");
    UI::Logging::log("u16 D = 0x1234;\n\n");
    UI::Logging::log(format(buff, "Decimal value of A: %i\n", A));
    UI::Logging::log(format(buff, "Heximal value of B: 0x%x\n", B));
    UI::Logging::log(format(buff, "Octal value of B: %o\n", B));
    UI::Logging::log(format(buff, "Value of C: %s\n", C));
    UI::Logging::log(format(buff, "Binary value of D: %b\n", D));
    
    //Early memory allocation (Basic malloc, free)
    //Initialize memory management
    //End early memory allocation
    //Initialize interrupt

    //Compile information
    //Build Unified System Call Interface (Register system call interrupt, support POSIX)
    //IDK

    while (true);
}
