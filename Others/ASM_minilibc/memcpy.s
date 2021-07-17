BITS 64

GLOBAL memcpy

memcpy:             ; (char *s1, char *s2, size_t size)
    push rbp        ; prologue
    mov rbp, rsp    ; prologue

    mov rcx, 0      ; i = 0

.loop:              ; v
    cmp rcx, rdx    ; while (i != size)
    je .end         ; ^
    mov al, byte [rsi + rcx]    ; a = s2[i]
    mov byte [rdi + rcx], al    ; s1[i] = a
    inc rcx         ; i++
    jmp .loop       ; 

.end:
    mov rax, rdi    ; return = s1
    leave           ; epilogue
    ret             ; epilogue