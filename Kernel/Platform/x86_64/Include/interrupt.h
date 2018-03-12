#pragma once
#include <types.h>

namespace Interrupt {
inline void enable_interrupt();
inline void disable_interrupt();

void init();

// typedef struct{

// } __attribute__((packed)) IDT_PTR

// typedef struct{

// } __attribute__((packed)) IDT_ENTRY;

}
