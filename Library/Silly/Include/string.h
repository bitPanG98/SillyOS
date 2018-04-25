#pragma once

#include <types.h>
#include <stdarg.h>

#define MAX_STRING_LENGTH 512

/* string.cxx */
char* Format(const char *fmt, ...);
u32 vFormat(char *buff, const char *fmt, va_list vl);

u8 ToInt(u64 num, char base, char *buff);

void ToLower(char *text);
void ToUpper(char *text);

u64 CopyMemory(void *des, const void *src, u64 n);
u64 SetMemory(void *des, u8 src, u64 n);
bool CmpMemory(void *to, void *from);