;File: entry.asm
;Description: System entry for x86_64 platform.

;Road to Rusty core
extern platform_rust_entry ;ssss~sss~ss~s~snake_case!
;
global platform_entry
;Global our addresses
global KERNEL_STACK_TOP
global KERNEL_STACK_BOTTOM
global KERNEL_HEAP_TOP
global KERNEL_HEAP_BOTTOM

[bits 64]
;We assume the caller are using fastcall call convention,
;by default, the caller will pass a magic number and a address that point to the needed info. though
;rcx and rdx.

;Everything start from here.
PLATFORM_ENTRY:
    ;Setup stack
    mov rsp, KERNEL_STACK_TOP


section .bss
;kernel stack
KERNEL_STACK_BOTTOM:
resb 4096   ;reserve one 4K page for our kernel
;stack grow from the top
KERNEL_STACK_TOP:

section .kernel_heap
KERNEL_HEAP_TOP:
resb 4096   ;reserve some space for our kernel heap
KERNEL_HEAP_BOTTOM: