#pragma once
#include <Types.h>



#define STRING_MAX_LEN 4096

//Get length of string (calculating char from start to '\0')
u32 Strlen(char *src){
    char *ptr = src;
    u32 len = 0;
    while(*ptr != '\0'){
        ptr++;
        len++;
    }
    return len;
}

u32 StrCpy(const char *src, char *dst){
    u32 len = 0;
    char *ptr = src;
    while(*ptr != '\0'){
        dst[len] = *ptr;
        ptr++;
        len++;
    }
    return len;
}