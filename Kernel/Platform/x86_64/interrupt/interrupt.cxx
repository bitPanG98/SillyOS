#include <interrupt.h>

namespace Interrupt {
inline void EnableInterrupt() { asm("cli"); }
inline void DisableInterrupt() { asm("sti"); }

void Initialize(){
    
}

}
