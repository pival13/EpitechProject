BITS 64

GLOBAL strpbrk

strpbrk:                      ; (char *s, char *poss)
    push rbp                  ; prologue
    mov rbp, rsp              ; prologue

    mov rax, 0                ; result = 0

    cmp rdi, 0                ;
    je .end                   ; if (s == NULL || poss == NULL)
    cmp rsi, 0                ;   return
    je .end                   ;

    mov rax, rdi              ; result = s
    mov r8, rsi               ; str = poss
    mov rcx, 0                ; i = 0
    jmp .loop_s1              ;

.loop_s1:                     ; while (1) {
    cmp byte [rax], 0         ;   if (result[0] == 0)
    je .end_0                 ;     exit(0)
    mov rcx, 0                ;   i = 0
    jmp .loop_s2              ;
.loop_s2:                     ;   while (1) {
    cmp byte [r8 + rcx], 0    ;     if (str[i] == 0)
    je .end_loop              ;       break
    mov dil, byte [r8 + rcx]  ;     a = str[i]
    cmp [rax], dil            ;     if (result[0] == a)
    je .end                   ;       return
    inc rcx                   ;     i++
    jmp .loop_s2              ;   }
.end_loop:                    ;
    inc rax                   ;   result++
    jmp .loop_s1              ; }

.end:                         ;
    leave                     ; epilogue
    ret                       ; epilogue

.end_0:                       ;
    mov rax, 0                ; result = 0
    jmp .end                  ; return