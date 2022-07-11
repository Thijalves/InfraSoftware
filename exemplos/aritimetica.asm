org 0x7c00            
jmp main
data:

main:
xor ax, ax
mov ds, ax
mov es, ax
mov ah, 0xe    

mov al, 48       ; movemos o character '0' para al
call _putchar


add al, 1       ; add -> soma dois parametros. nesse caso al virará 49 ( '1' na tabela ascii)
call _putchar


mov bl, 5      ; move 5 para bl
add al,bl      ; add funciona com registradores. aqui bl será somado a al
call _putchar

mov cl, 5     
sub al, cl    ; para subtrair usamos a instrução sub
call _putchar	

jmp $


_putchar:
	mov ah, 0xe    
	int 10h
	ret


times 510-($-$$) db 0
dw 0xaa55

