; rax: retour, rdi: param (str)

section	.text
	global		ft_strlen

ft_strlen:
			cmp		rdi, 0
			jz		null
        	mov		rax, 0
			jmp		compare

increment:
			inc		rax

compare:
			cmp		BYTE [rdi + rax], 0
			jne		increment

done:
			ret

null
			mov		rax, -1
			ret