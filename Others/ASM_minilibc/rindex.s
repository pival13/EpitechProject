BITS 64

GLOBAL rindex

rindex:                         ; (char *s, char c)
    push rbp                    ; prologue
    mov rbp, rsp                ; prologue

    mov rax, 0                  ; return = NULL
    
    cmp rdi, 0                  ; if (s == NULL)
    je .end                     ;   goto .end

.loop:
    cmp byte [rdi], sil         ; if (*s == c)
    je .exit_loop               ;   goto .exit_loop
.loop_next:
    cmp byte [rdi], 0           ; if (*s == 0)
    je .end                     ;   goto .end
    inc rdi                     ; s++
    jmp .loop                   ; goto .loop

.exit_loop:
    mov rax, rdi                ; return = s
    jmp .loop_next              ; goto .loop_next

.end:
    leave                       ; epilogue
    ret                         ; epilogue