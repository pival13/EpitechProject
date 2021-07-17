BITS 64

GLOBAL strlen

strlen:
    push rbp                ; prologue
    mov rbp, rsp            ; prologue    

    mov rax, 0              ; rax = 0

    cmp rdi, 0              ; if rdi == null return
    je .end                 ; ^

.loop:                      ; v
    cmp byte [rdi + rax], 0 ; while param[rax] != 0
    je .end                 ; ^
    inc rax                 ; rax++
    jmp .loop               ; end

.end:
    leave                   ; epilogue
    ret                     ; epilogue