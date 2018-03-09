  ; 3=====================================================================D
  ;     @File:    entry.asm
  ;     @Path:  /Kernel/Platform/x86_64/src
  ;     @Authors:   KeyboardMayCry[eddy199883@gmail.com]
  ;     @Descriptions:  System entry for x86_64 platform.
  ;     @Updates:
  ;        12 Jan 2018    ||  KeyboardMayCry  ||  File Created. 
  ; 3=====================================================================D
[bits 64]
global PLATFORM_ENTRY
;Global our addresses
global KERNEL_STACK_TOP
global KERNEL_STACK_BOTTOM
global KERNEL_HEAP_TOP
global KERNEL_HEAP_BOTTOM

extern kernel_init


;Header defines
; MAGIC equ 0x1A534F53 ;Magic spell (4 bytes)   0x1A, 'SOS'
; ENTRY_OFFSET equ PLATFORM_ENTRY - HEADER_START  ;Entry offset
; CHECKSUM equ -(ENTRY_OFFSET + MAGIC)

section .entry
; HEADER_START:
;   dd MAGIC
;   dd ENTRY_OFFSET
;   dd CHECKSUM
; HEADER_END:
;Everything start from here.
PLATFORM_ENTRY:
    ;no interrupt for now
    cli
    ;Setup stack
    mov rbp, KERNEL_STACK_TOP
    mov rsp, rbp
    
    ; we assume rdi stored the address of the booting infomation
    call kernel_init
    ;if we unluckily get here, we need to stop it
    cli
    hlt

section .bss
KERNEL_STACK_BOTTOM:
resb 4096 * 2 ; 2 * 4K page
KERNEL_STACK_TOP:
