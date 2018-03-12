#include <memory.h>

namespace Memory::EarlyAllocation {
    //Find us in x86_64.asm
    extern "C" u8 KERNEL_HEAP_START;
    extern "C" u8 KERNEL_HEAP_END;
    extern "C" u8 KERNEL_BLOCK_TABLE_START;
    extern "C" u8 KERNEL_BLOCK_TABLES_END;
    extern "C" u8 BLOCK_SIZE;

    static void *heap_start = &KERNEL_HEAP_START;
    static void *heap_end = &KERNEL_HEAP_END;
    static u8 *block_list = &KERNEL_BLOCK_TABLE_START;
    static u32 max_block = (&KERNEL_HEAP_END - &KERNEL_HEAP_START) / BLOCK_SIZE;

    void init(){
        u8 *ptr = (u8 *)heap_start;
        while(ptr != heap_end){
            *ptr = 0;
            ptr++;
        }
        ptr = block_list;
        while(ptr != &KERNEL_BLOCK_TABLES_END){
            *ptr = 0;
            ptr++;
        }
    }

    // void* malloc(u32 size){
    //     u32 block_size = size < BLOCK_SIZE ? 1 : size / BLOCK_SIZE;
    //     u32 counter = 0;
    //     while(counter != block_size){
    //         while(true){
                
    //         }
    //     }

    // }

    // void free(void* ptr){

    // }


}