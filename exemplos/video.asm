org 0x7c00            ; seleciona modo de video e muda cor da tela para vermelho
jmp _main

_data:
imagem db "16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 7, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 7, 8, 8, 8, 8, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 8, 8, 8, 8, 9, 1, 8, 8, 8, 8, 1, 8, 0, 0, 0, 0, 0, 0, 8, 8, 9, 9, 9, 9, 8, 9, 9, 8, 0, 0, 0, 0, 0, 0, 8, 1, 9, 9, 15, 15, 9, 9, 9, 8, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 8, 9, 15, 15, 15, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9, 15, 15, 9, 9, 9, 8, 0, 0, 0, 0, 8, 8, 8, 8, 1, 9, 9, 9, 9, 8, 8, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 8, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0", 0

_main:
xor ax, ax  ;zera ax, xor é mais rápido que mov
mov ds, ax  ;zera ds (não pode ser zerado diretamente)
mov cx, ax  ;zera cx
mov es, ax  ;zera es
mov dx, ax

call _clear  ;  nesta função setamos o boot para modo de video

mov ah,0xb   ; 1º parametro para modo de video
mov bh, 0    ; 2º parametro para modo de video
mov bl, 0    ; cor da tela. podemos escolher entre 1 e 15
int 10h

mov ah, 0ch ; coloca no modo de pintar pixels

mov si, imagem

.for1:
cmp dx, 16
je .fim1
mov cx, 0
jmp .for2
jmp .for1

.fim1:
ret

.for2:
cmp cx, 16
je .fim2
mov al, 0fh
int 10h
inc cx
jmp .for2

.fim2:
inc dx
jmp .for1


_clear:
mov ah, 0       ; primeiro parametro para chamar modo de video
mov al, 13h     ; segundo parametro para chamar modo de video
int 10h
ret

jmp $

times 510-($-$$) db 0
dw 0xaa55

