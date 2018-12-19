; 3===========================================================D
;     @File:  one.asm
;     @Path:  /Bootloader/x86_64/Legacy
;     @Authors:   KeyboardMayCry
;     @Descriptions:  
;
;     @Updates:
;         12 Jan 2018  ||    KeyboardMayCry    ||  File Created.
; 3===========================================================D
%include "two.asm"
global IN_REAL_MODE
[bits 16]
org 0x7c00
section .text
IN_REAL_MODE:
	;Clear registers
	xor ax, ax
	mov bx, ax
	mov cx, ax
	mov dx, ax

	mov cs, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov si, ax
	mov sp, ax

	; self loading

	; activate A20

	; goto protected mode