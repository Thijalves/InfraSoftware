org 0x7c00
jmp _start

_putchar:
    mov ah, 0xe
    int 10h
    ret

_getchar:
    mov ah, 0x00 ; configura pra ler um char
    int 16h
    ret

_start:
    ; limpa os registradores
    xor ax, ax  
    xor bx, bx 

    ; seta o movo de video
    mov ah, 00h
    mov al, 00h
    int 10h

    .lerchar:
        mov ah, 0x00 ; configura pra ler um char
        int 16h
        cmp al, ' '
        je  .fim
        mov ah, 0xe
        int 10h
        mov ah, 0xe
        mov al, 13
        int 10h
        jmp .lerchar
    
    .fim:
        jmp $

    ;printa o char lido
    mov ah, 0xe
    int 10h
   


times 510-($-$$) db 0
dw 0xaa55