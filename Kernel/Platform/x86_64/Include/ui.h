#pragma once
#include <types.h>
#include <stdarg.h>

namespace UI {
/* ui.cxx*/
u32 str_format(char *buff, char *str, ...);
}

#define DEFAULT_TEXT_COLOR 0xffffff
#define DEFAULT_BG_COLOR 0x252525

namespace UI::Terminal {
/*  terminal.cxx   */
void init();
void write(char *);
void put(char);
void set_pos(u32, u32);
void get_pos(u32*, u32*);
bool valid_pos(u32, u32);
void set_color(u32);
}

namespace UI::Logging {
/* logging.cxx */
void log(char*, ...);
void assert(bool);
}


