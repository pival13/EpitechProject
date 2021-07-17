BITS 64

GLOBAL strcspn

strcspn:                      ; (char *s, char *forbid)
    push rbp                  ; prologue
    mov rbp, rsp              ; prologue

    cmp rdi, 0                ; if s == 0
    je .end_0                 ;  exit 0
    cmp rsi, 0                ; if forbid == 0
    je .end_0                 ;  exit 0

    mov rax, rdi              ; res = s
    mov rcx, 0                ; i = 0
    jmp .loop_s1              ;

.loop_s1:                     ; while 1
    cmp byte [rax], 0         ;  if res[0] == 0
    je .end                   ;   break
    mov rcx, 0                ;  i = 0
    jmp .loop_s2              ;
.loop_s2:                     ;  while 1
    cmp byte [rsi + rcx], 0   ;   if forbid[i] == 0
    je .end_loop              ;    break
    mov dl, byte [rsi + rcx]  ;   a = forbid[i]
    cmp [rax], dl             ;   if s[0] == a
    je .end                   ;    return
    inc rcx                   ;   i++
    jmp .loop_s2              ;  
.end_loop:                    ;
    inc rax                   ;  res++
    jmp .loop_s1              ;

.end:                         ;
    sub rax, rdi              ; res -= s
    leave                     ; epilogue
    ret                       ; epilogue

.end_0:                       ;
    mov rax, rdi                ; res = s
    jmp .end                  ; return