org 0x7c00            ; “Oi”
jmp main  ; pula para main
data:

main:
xor ax, ax      ; "limpa" os registradores as,ds,es
mov ds, ax
mov es, ax


mov al, 'O'   ; aramazena o character 'O' em al
mov ah, 0xe   ; armazena o numero de interrupção 0xe em ah
int 10h       ; chama a interrupção

mov al, 'i'   ; aramazena o character 'i' em al
mov ah, 0xe   ; armazena o numero de interrupção 0xe em ah
int 10h       ; chama a interrupção


times 510-($-$$) db 0
dw 0xaa55
