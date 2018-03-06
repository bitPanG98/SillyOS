global change_rflag
section .text
;BUGGY
change_rflag:
    push rcx    ;backup rcx 1
    pushfq  ;backup current RFLAG register , so call FLAG_A 2
    pushfq  ;push current RFLAG to the stack, so call FLAG_B    3
    mov rax, qword [rsp]  ;store flag
    xor qword [rsp], 0x200000 ;invert bit 21 of FLAG_B
    popfq   ;bring FLAG_B back to cpu   2
    pushfq  ;FLAG_C 3
    pop rcx ;pop FLAG_C to rcx  2
    popfq   ;pop back FLAG_A    1
    and rax, 0x200000    ;we only need bit 21
    and rax, rcx    ;0: if not change, 1: change
    pop rcx ;pop back rcx   0
    ret