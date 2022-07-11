org 0x7c00
jmp _start

_data:

string db "ola, mundo!", 0

_start:
xor ax, ax     ; limpa reigistradores
mov ds, ax
mov es, ax

mov si, string
    .loop1:
        lodsb
    cmp al, 0          ; cmp -> essa instrução compara dois parametros. aqui ela checa se al é igual a 0
    je .fim	   ; je -> essa instrução checa o resultado de cmp. se for igual ela pula para .fim
    call _putchar      ; printa caratere
    jmp .loop1  
    jmp $

    .fim:
        ret

_putchar:
    mov ah, 0xe
    int 10h
    ret


times 510-($-$$) db 0
dw 0xaa55