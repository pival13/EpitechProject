BITS 64

GLOBAL strcasecmp

strcasecmp:                   ; (char *s1, char *s2)
    push rbp                  ; prologue
    mov rbp, rsp              ; prologue

    mov rax, 0                ; result = 0
    mov rcx, 0                ; i = 0

.loop:                        ; while(1) {
    jmp .comp                 ;   comp()
.loopn:
    cmp al, ah                ;   if (al != ah)
    jne .exit                 ;     exit()
    cmp al, 0                 ;   if (al == 0)
    je .end0                   ;     break;
    inc rcx                   ;   i++
    jmp .loop                 ; }

.comp:                        ; comp() {
    mov al, byte [rdi + rcx]  ;   al = s1[i]
    cmp al, 0x41              ;    v
    jl .comp2                 ;   if (al >= 'A' || al <= 'Z')
    cmp al, 0x5A              ;     al += 'a' - 'A' (32 = 0x20)
    jg .comp2                 ;    ^
    add al, 0x20              ;    ^

.comp2:                       ; 
    mov ah, byte [rsi + rcx]  ;   ah = s2[i]
    cmp ah, 0x41              ;    v
    jl .loopn                 ;    v
    cmp ah, 0x5A              ;   if (ah >= 'A' || ah <= 'Z')
    jg .loopn                 ;     ah += 'a' - 'A'
    add ah, 0x20              ;    ^
    jmp .loopn                ; }

.exit:
    mov al, byte[rdi + rcx]
    cmp byte[rsi + rcx], al     
    jl .end_1

.end1:
    mov rax, 1
    jmp .end
.end_1:
    mov rax, -1
    jmp .end
.end0:
    mov rax, 0
    jmp .end
.end:
    leave                     ; epilogue
    ret                       ; epilogue