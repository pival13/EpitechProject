BITS 64

GLOBAL strchr

strchr:                        ; (char *s, char c)
    push rbp                   ; prologue
    mov rbp, rsp               ; prologue

    mov rax, 0                 ; result = 0

    cmp rdi, 0                 ; if (s == NULL)
    je .end                    ;   return

.loop:                         ; while(1) {
    cmp [rdi], sil             ; if (*s == c)
    je .exit_loop              ;   return
    cmp byte [rdi], 0          ; if (*s == 0)
    je .end                    ;   return
    inc rdi                    ; s++
    jmp .loop                  ; }

.exit_loop:                    ; 
    mov rax, rdi               ; result = s

.end:                          ;
    leave                      ; epilogue
    ret                        ; epilogue