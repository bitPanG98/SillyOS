#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include <types.h>

inline void enable_interrupt();
inline void disable_interrupt();

void interrupt_init();

#endif
