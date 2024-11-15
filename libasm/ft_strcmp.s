; rdi = 1er param (*s1), rsi = 2e param (*s2), rcx = compteur

section	.text
	global		ft_strcmp

ft_strcmp:
        	mov		rcx, 0
			test	rdi, rdi
			jz		null
			test	rsi, rsi
			jz		null
			jmp		compare

null:
			mov		rax, -1
			ret

compare:
			mov		dl, BYTE [rdi + rcx]
			cmp		dl, BYTE [rsi + rcx]
			jne		not_equal

check_end:
			cmp		BYTE [rdi + rcx], 0
			je		equal

			inc		rcx

			jmp		compare

not_equal:
			movzx	rax, BYTE [rdi + rcx]
			movzx	rbx, BYTE [rsi + rcx]
			sub		rax, rbx

			ret

equal:
			mov		rax, 0
			ret