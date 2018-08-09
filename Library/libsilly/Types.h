#pragma once

/*  Primitive types */
//signed
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
//unsigned
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define PACKED __attribute__((packed))

#define null ((void*)0)