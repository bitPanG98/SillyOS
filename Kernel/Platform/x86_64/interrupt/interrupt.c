#include <interrupt.h>

inline void enable() { asm("cli"); }
inline void disable() { asm("sti"); }

