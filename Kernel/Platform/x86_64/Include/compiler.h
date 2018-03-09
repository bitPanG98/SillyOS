#pragma once
/*
    This header file do nothing to the kernel itself!
*/
#ifdef __linux__
#error "Use cross-compiler PLS!"
#endif

#ifndef __x86_64__
#error "Wrong target!"
#endif
