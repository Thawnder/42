; rdi = 1er param (fd), rsi = 2e param (buffer), rdx = 3eme param (size)

section .text
		extern __errno_location
		global ft_read

ft_read:  
		movsxd	rdi, edi

		cmp		rdi, 0
		jl		invalid_fd

		cmp		rdi, 1
		je		invalid_fd

		cmp		rdi, 2
		je		invalid_fd

		cmp		rdx, 0
		jl		invalid_size

		cmp		rsi, 0
		je		null

		mov		rax, 0
		syscall
		cmp		rax, 0
		jl		invalid_fd
    
end:        
		ret

null:
		cmp		rdx, 0
		jne		invalid_size
		jmp		end

invalid_fd:
		call 	__errno_location wrt ..plt
		mov 	dword [rax], 9                ; 9: EBADF (Bad file descriptor)
		jmp 	error

invalid_size:
		call 	__errno_location wrt ..plt
		mov 	dword [rax], 14               ; 14: EFAU (Invalid argument)
		jmp 	error

error:
		mov 	rax, -1
		ret