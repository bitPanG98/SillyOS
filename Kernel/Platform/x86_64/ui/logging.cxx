#include <ui.h>
#include <peripheral.h>
#include <stdarg.h>
#include <string.h>

namespace UI::Logging
{
void log(char *str){
    Peripheral::Serial::write(str);
    UI::Terminal::write(str);
}

void assert(bool condition)
{
}
}