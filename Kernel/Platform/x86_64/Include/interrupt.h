#pragma once
#include <types.h>

namespace Interrupt {
inline void EnableInterrupt();
inline void DisableInterrupt();

void Initialize();

typedef struct{
    u16 Limit;
    u64 Offset;
} __attribute__((packed)) IDT_PTR;

typedef struct{
    u16 OffsetLow;
    u16 Selector;
    u8 Zero;
    u8 Attribute;
    u16 OffsetMid;
    u32 OffsetHigh;
    u32 Zero2;
} __attribute__((packed)) IDT_ENTRY;

}
