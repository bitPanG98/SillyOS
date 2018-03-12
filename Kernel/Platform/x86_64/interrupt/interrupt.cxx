#include <interrupt.h>

namespace Interrupt {
inline void enable() { asm("cli"); }
inline void disable() { asm("sti"); }

void init(){
    
}

}
