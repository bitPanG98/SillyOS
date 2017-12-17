;File: entry.asm
;Description: System entry for x86_64 platform.

;Road to Rusty core
extern platform_rust_entry ;ssss~sss~ss~s~snake_case!
;
global PLATFORM_ENTRY
;Global our addresses
global KERNEL_STACK_TOP
global KERNEL_STACK_BOTTOM
global KERNEL_HEAP_TOP
global KERNEL_HEAP_BOTTOM

[bits 64]
;We assume the caller are using fastcall call convention,
;by default, the caller will pass a magic number and a address that point to the needed info. though
;rcx and rdx.
section .start
;Everything start from here.
PLATFORM_ENTRY:
    ;Setup stack
    mov rsp, KERNEL_STACK_TOP
    mov rbp, KERNEL_STACK_TOP


    ;In win64 to Rust call convention
    ;mov rdi, rcx    ;First arguments contain the Magic number
    ;mov rsi, rdx    ;and the second one contain the potiner of the table


    ;Didnt move arguments of EFI function, so the arguments the bootloader passed will still in place.
    ;ecx: Magic number  rdx: Pointer of the table
    call platform_rust_entry
    ;if we unluckily go here, we need to stop it
    cli
    hlt

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