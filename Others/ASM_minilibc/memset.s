BITS 64

GLOBAL memset

memset:                         ; (void *s, int char, size_t size)
    push rbp                    ; prologue
    mov rbp, rsp                ; prologue

    mov rax, rdi                ; return = s
    mov rcx, 0                  ; i = 0

    cmp rdi, 0                  ; if (s == NULL)
    je .end                     ;   goto .end

.loop:
    cmp rcx, rdx                ; if (i == size)
    je .end                     ;   goto .end
    mov byte [rdi + rcx], sil  ; s[i] = char
    inc rcx                     ; i++
    jmp .loop                   ; goto .loop

.end:
    leave                       ; epilogue
    ret                         ; epilogue