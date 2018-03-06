global _inb
global _inw
global _indw

global _outb
global _outw
global _outdw

;edi: port esi: data
section .text
;Port input
_inb:
    xor rax, rax    ;clear rax
    mov dx, di  ;16bit port
    in al, dx ;get a byte
    ret

_inw:
    xor rax, rax
    mov dx, di
    in ax, dx ;get 2 byte
    ret

_indw:
    xor rax, rax
    mov dx, di
    in eax, dx    ;get 4 byte
    ret
;Port output
_outb:
    mov dx, di  ;16bit port
    mov ax, si
    out dx, al
    ret

_outw:
    mov dx, di  ;16bit port
    mov ax, si
    out dx, ax
    ret

_outdw:
    mov dx, di  ;16bit port
    mov eax, esi
    out dx, eax
    ret