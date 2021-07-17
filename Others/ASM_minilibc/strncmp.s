BITS 64

GLOBAL strncmp

strncmp:                       ; (char *s1, char *s2)
    push rbp                   ; prologue
    mov rbp, rsp               ; prologue

    mov rcx, 0                 ; i = 0

.loop:                         ; while (1) {
    mov al, byte [rsi + rcx]   ;   a = [s2[i]]
    cmp byte [rdi + rcx], al   ;   if (s1[i] > a) return 1
    jg .end1                   ;   else if (s1[i] < a) return -1
    jl .end_1
    cmp byte [rdi + rcx], 0    ;   if (s1[i] == 0)
    je .end0                   ;     break
    cmp rcx, rdx               ;   if (i == n)
    je .end0                   ;     return 0
    inc rcx                    ;   i++
    jmp .loop                  ; }

.end1:
    mov rax, 1
    jmp .end
.end_1:
    mov rax, -1
    jmp .end
.end0:
    mov rax, 0
    jmp .end
.end:                          ;
    leave                      ; epilogue
    ret                        ; epilogue