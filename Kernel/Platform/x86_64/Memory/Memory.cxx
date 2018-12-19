#include <Memory.h>
#include <UI.h>
#include <Booting.h>

namespace Memory {
    void Initialize(void *memMap, u64 memMapSize, u64 descSize){
        u8 *ptr = (u8 *)memMap;
        while(ptr < memMap + memMapSize){
            
            ptr += descSize;
        }
    }
}