; rdi = 1er param (*s1), rcx = compteur, rdx = char temporaire

section	.data
	null_msg 	db "Src is null", 10, 0
	malloc_msg	db "Allocation error", 10, 0

section	.text
	global		ft_strdup
	extern		malloc
	extern		__errno_location

ft_strdup:
		cmp		rdi, 0
		jz		null_ptr

len_init:
		mov		rcx, 0
		jmp		end_of_string

len_inc:
		inc		rcx

end_of_string:
		cmp		BYTE [rdi + rcx], 0
		jne		len_inc

malloc_dest:
		inc		rcx
		push	rdi
		mov		rdi, rcx
		call    malloc wrt ..plt
		pop		rdi
		cmp		rax, 0
		jz		malloc_error

copy_init:
		mov		rcx, 0
		mov		rdx, 0
		jmp		copy_string

copy_inc:
		inc		rcx

copy_string:
		mov		dl, BYTE [rdi + rcx]
		mov		BYTE [rax + rcx], dl
		cmp		dl, 0
		jnz		copy_inc
		jmp		return

null_ptr:
		lea		rax, [rel null_msg]
		ret

malloc_error:
		call	__errno_location wrt ..plt
		mov		dword [rax], 12 ; 12: out of memory / en gros on fait errno = ENOMEM
		lea		rax, [rel malloc_msg]	
		ret

return:
		ret