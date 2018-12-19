[bits 64]
global PLATFORM_ENTRY
global FlushGDT
;Global our addresses
global KERNEL_STACK_TOP
global KERNEL_STACK_BOTTOM

extern PlatformMain

BLOCK_SIZE equ 8
KERNEL_HEAP_SIZE equ 2
KERNEL_STACK_SIZE equ 2

section .entry
;Everything start from here.
PLATFORM_ENTRY:
    ;Disable interrupt
    cli
    ;Setup stack
    mov rbp, KERNEL_STACK_TOP
    mov rsp, rbp
    
    ; we assume rdi stored the address of the booting infomation
    call PlatformMain
    ;if we somehow get in here, we need to stop it
    cli
    hlt
    dd BLOCK_SIZE

;See https://github.com/tianocore/edk2/blob/master/UefiCpuPkg/CpuDxe/X64/CpuAsm.nasm
;Thanks to MouseOS: http://www.mouseos.com/os/tools/nasm.html
FlushGDT:
  ;edi: code esi: data
  ;allocate 16 byte
  sub rsp, 0x10
  lea rax, [.rocket_jump]
  mov [rsp], rax
  mov [rsp+4], di
  jmp dword far [rsp]
.rocket_jump:
  ;restore stack
  add rsp, 0x10
  mov ax, si
  mov es, ax
  mov ds, ax
  mov gs, ax
  mov fs, ax
  mov ss, ax
  ret

  
section .bss
KERNEL_STACK_BOTTOM:
resb 4096 * KERNEL_STACK_SIZE ; 2 * 4K page
KERNEL_STACK_TOP: