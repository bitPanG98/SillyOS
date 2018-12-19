#pragma once
#include <Types.h>

void MemSet(const u8 src, void *dst, u64 n){
    for (auto i = 0; i < n; i++){
        ((char *)dst)[i] = src;
    }
}

void MemCpy(const void *src, const void *dst, u64 n){
    for (auto i = 0; i < n; i++){
        ((char *)dst)[i] = ((char *)src)[i];    
    }
}

bool MemCmp(const void *src, const void *dst, u64 n){
    char *temp = (char *)src;
    for (auto i = 0; i < n; i++){
        if(*temp != *((char *)dst)){
            return false;
        }
    }
    return true;
}