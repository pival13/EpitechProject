BITS 64

GLOBAL memmove

memmove:                        ; (char *dest, char *src, size_t size)
    push rbp                    ; prologue
    mov rbp, rsp                ; prologue

    mov rax, 0

    cmp rdx, 0
    je .end
    cmp rdi, 0
    je .end_0
    cmp rsi, 0
    je .end_0

    cmp rdi, rsi                ; if (dest < src)
    jg .loopgb                  ; {

    mov rcx, 0                  ;   i = 0
.loopl:
    cmp rcx, rdx                ;   while (i != size)
    je .end                     ;   {
    mov al, byte [rsi + rcx]    ;     a = src[i]
    mov byte [rdi + rcx], al    ;     dest[i] = a
    inc rcx                     ;     i++
    jmp .loopl                  ;   }

.loopgb:                        ; } else {
    mov rcx, rdx                ;   i = size
.loopg:
    dec rcx                     ;     i--
    mov al, byte [rsi + rcx]    ;     a = src[i]
    mov byte [rdi + rcx], al    ;     dest[i] = a
    cmp rcx, 0                  ;   while (i != 0)
    je .end                     ;   {
    jmp .loopg                  ;   }

.end:                           ; }
    mov rax, rdi                ; return = dest
.end_0:
    leave                       ; epilogue
    ret                         ; epilogue