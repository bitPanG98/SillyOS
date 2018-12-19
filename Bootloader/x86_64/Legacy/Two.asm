; 3===========================================================D
;     @File:  two.asm
;     @Path:  /Bootloader/x86_64/Legacy
;     @Authors:   KeyboardMayCry
;     @Descriptions:  
;
;     @Updates:
;         12 Jan 2018  ||    KeyboardMayCry    ||  File Created.
; 3===========================================================D
%include "three.asm"
[bits 32]
IN_PROTECTED_MODE:
    ; setup gdt

    ;setup paging

    ;toggle MSR

    ;goto flat mode