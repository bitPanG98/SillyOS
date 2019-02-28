#pragma once

#include <Types.h>

inline void MemSet(const u8 src, void *dst, u64 n){
    for (auto i = 0; i < n; i++){
        ((char *)dst)[i] = src;
    }
}

inline void MemCpy(const void *src, const void *dst, u64 n){
    for (auto i = 0; i < n; i++){
        ((char *)dst)[i] = ((char *)src)[i];    
    }
}

inline bool MemCmp(const void *src, const void *dst, u64 n){
    char *temp = (char *)src;
    for (auto i = 0; i < n; i++){
        if(*temp != *((char *)dst)){
            return false;
        }
    }
    return true;
}