BITS 64

GLOBAL strcmp

strcmp:                         ; (char *s1, char *s2)
    push rbp                    ; prologue
    mov rbp, rsp                ; prologue

    mov rax, 0                  ; result = 0

.loop:                          ; while 1
    mov al, byte [rsi]          ;  
    cmp byte [rdi], al          ;  if *s1 != *s2
    jg .end1
    jl .end_1
    cmp byte [rdi], 0           ;  if *s1 == 0
    je .end0                    ;   return
    inc rdi                     ;  s1++
    inc rsi                     ;  s2++
    jmp .loop                   ;

.end1:
    mov rax, 1
    jmp .end
.end_1:
    mov rax, -1
    jmp .end
.end0:
    mov rax, 0
    jmp .end
.end:                           ;
    leave                       ; epilogue
    ret                         ; epilogue