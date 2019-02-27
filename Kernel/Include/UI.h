#pragma once
#include <Types.h>
#include <Peripheral.h>

#define DEFAULT_TEXT_COLOR 0xffffff
#define DEFAULT_BG_COLOR 0x252525

/*  Marcos  */
#define LOG(x)\
Peripheral::Serial::Write((x));\
UI::Terminal::Write((x));

#define PANIC(x)\
Peripheral::Serial::Write("[Panic!] ");\
Peripheral::Serial::Write((x));\
UI::Terminal::Write("[");\
UI::Terminal::SetColor(0xff0000);\
UI::Terminal::Write("Panic!");\
UI::Terminal::Write("] ");\
UI::Terminal::Write((x));\
while(true);

#define DEBUG(x, y)\
if((x) == true){\
    LOG((y));\
}

namespace UI::Terminal {
/*  terminal.cxx   */
void Initialize();
void Write(char *);
void Write(char);
void SetPos(u32, u32);
void GetPos(u32*, u32*);
bool CheckPos(u32, u32);
void SetColor(u32);
}

