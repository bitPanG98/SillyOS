#pragma once

#include <Types.h>
#include <stdarg.h>

#define MAX_STRING_LENGTH 512

/* string.cxx */
UNSAFE char* Format(const char *fmt, ...);
UNSAFE u32 vFormat(char *buff, const char *fmt, va_list vl);

UNSAFE u8 ToInt(u64 num, char base, char *buff);

UNSAFE void ToLower(char *text);
UNSAFE void ToUpper(char *text);

UNSAFE u64 CopyMemory(void *des, const void *src, u64 n);
UNSAFE u64 SetMemory(void *des, u8 src, u64 n);
UNSAFE bool CmpMemory(void *to, void *from, u64 n);