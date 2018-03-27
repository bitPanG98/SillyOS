global inb
global inw
global indw

global outb
global outw
global outdw

;edi: port esi: data
section .text
;Port input
inb:
    xor rax, rax    ;clear rax
    mov dx, di  ;16bit port
    in al, dx ;get a byte
    ret

inw:
    xor rax, rax
    mov dx, di
    in ax, dx ;get 2 byte
    ret

indw:
    xor rax, rax
    mov dx, di
    in eax, dx    ;get 4 byte
    ret
;Port output
outb:
    mov dx, di  ;16bit port
    mov ax, si
    out dx, al
    ret

outw:
    mov dx, di  ;16bit port
    mov ax, si
    out dx, ax
    ret

outdw:
    mov dx, di  ;16bit port
    mov eax, esi
    out dx, eax
    ret