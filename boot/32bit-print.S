[bits 32] ;Using 32-bit protected mode

VIDEO_MEMORY equ 0xb8000
WHITE_OB_BLACK equ 0x0f	  ;color byte for WHITE

print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY

print_string_loop:
	mov al,[ebx]		;[ebx] is address of string
	mov ah, WHITE_OB_BLACK

	cmp al, 0			;check if its ended
	je finish

	mov [edx], ax		;Store the position of string + attribute in edx(Video Memory)
	add ebx, 1			;next char
	add edx, 2
	jmp print_string_loop

finish:
	popa
	ret
