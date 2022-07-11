org 0x7c00            ;
jmp _start

_data:    

hello db "hello world!", 0        ; declara hello como um serie de bytes
    
_start:
xor ax, ax     ; limpa reigistradores
mov ds, ax
mov es, ax

mov si, hello     ; coloca em si o endereço de hello
call _print       ; chama a função print
call _fim

_putchar:
    mov ah, 0xe
    int 10h
    ret

_print:                    ; printa a string armazenada em si
    .loop1:       
    	lodsb	           ; lodsb -> essa instrução carrega al com o byte apontado por si e depois incrementa di
	cmp al, 0          ; cmp -> essa instrução compara dois parametros. aqui ela checa se al é igual a 0
	je .fim		   ; je -> essa instrução checa o resultado de cmp. se for igual ela pula para .fim
	call _putchar      ; printa caratere
	jmp .loop1         ; pula de volta para loop1, até a string terminar
	
    .fim:
	ret                ; retorna para o local onde a função foi chamada

_fim:
    jmp $                  ; jmp $ é uma forma de terminar o programa.

times 510-($-$$) db 0
dw 0xaa55
