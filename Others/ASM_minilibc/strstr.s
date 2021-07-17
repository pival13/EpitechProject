BITS 64

SECTION .text
GLOBAL strstr

strstr:                      ; (char *s, char *pattern)
    push rbp                 ; prologue
    mov rbp, rsp             ; prologue

    cmp rdi, 0               ; if (s == NULL || pattern == NULL)
    je .end_0                ;   goto .end
    cmp rsi, 0               ; ^
    je .end_0                ; ^

    mov rax, rdi             ; result = s

.loop_s1:                    ; while(1) {
    mov r8, rsi              ;   str = pattern
    mov r9, 0

.loop_s2:                    ;   while (1) {
    mov dl, byte [r8]        ;     a = *str
    cmp dl, 0         ;     if (*str == 0)
    je .end                  ;       return
    cmp byte [rax + r9], dl       ;     if (*result != a)
    jne .end_loop            ;       break
    inc r8                   ;     str++
    inc r9
    jmp .loop_s2             ;   }

.end_loop:                   ;   
    cmp byte [rax], 0        ;   if (rax[0] == 0)
    je .end_0                ;     exit(0)
    inc rax                  ;   result++
    jmp .loop_s1             ; }

.end_0:                      ;
    mov rax, 0               ; result = 0

.end:
    leave                    ; epilogue
    ret                      ; epilogue
