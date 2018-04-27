#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

#define null (void *)0

/*
    Coding sugar!
*/
#define UNSAFE


#ifndef __C_PLUS_PLUS
    #define bool u8
    #define true 1
    #define false 0
#endif

#endif
