#pragma once

#include <types.h>
#include <stdarg.h>

/* string.cxx */
UNSAFE char* format(char *buff, const char *fmt, ...);
UNSAFE u32 vformat(char *buff, const char *fmt, va_list vl);

UNSAFE u8 to_int(u64 num, char base, char *buff);

UNSAFE void to_lower(char *text);
UNSAFE void to_upper(char *text);

UNSAFE u64 copy_mem(void *des, const void *src, u64 n);
UNSAFE u64 set_mem(void *des, u8 src, u64 n);
UNSAFE bool cmp_mem(void *to, void *from);