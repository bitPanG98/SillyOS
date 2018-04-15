#pragma once
#include <types.h>

#define DEFAULT_TEXT_COLOR 0xffffff
#define DEFAULT_BG_COLOR 0x252525

/*  Marcos  */
#define LOG(x)\
Peripheral::Serial::Write(x);\
UI::Terminal::Write(x);

#define DEBUG(x, y)\
if(x == true){\
    LOG(y);\
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

