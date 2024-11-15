; donc là, rdi = 1er param (*dest), rsi = 2e param (*src)
; on utilise rcx comme compteur, et rdx comme registre pour stocker temporairement le caractere (un seul octet) a copier 
; (via DL, qui est l'octet partie basse de RDX)

section .data
	null_msg	db "Src or dst is null", 10, 0

section .text
	global		ft_strcpy

ft_strcpy:
        	mov		rcx, 0
			mov		rdx, 0
			cmp		rsi, 0
			jz		null
			cmp		rdi, 0
			jz		null
			jmp		copy

increment:
			inc		rcx

copy:
			mov		dl, BYTE [rsi + rcx]
			mov		BYTE [rdi + rcx], dl
			cmp		dl, 0
			jnz		increment

return:
			mov		rax, rdi
			ret

null:
			lea 	rax, [rel null_msg]
			ret