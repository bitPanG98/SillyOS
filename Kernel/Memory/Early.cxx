#include <Memory.h>

namespace Memory::Early {
    extern "C" u8 PRESERVED_MEMORY_HEAP;
    extern "C" u8 PRESERVED_MEMORY_HEAP_END;

    //pointed to current position
    static u8 *cursor;
    static u8 *heap_end = (u8 *)PRESERVED_MEMORY_HEAP_END;


    void Initialize(){
        cursor = (u8 *)PRESERVED_MEMORY_HEAP;

    }

    void* Allocate(u64 size){

    }

    bool Free(void *ptr){
        return false;
    }

}