diskload:
	pusha
	push dx
	mov ah, 0x02    ; 0x02 is function read
	mov al, dh      ; number of sectors to read (e.g. 0x01, 0x02)
	mov cl, 0x02    ; 0x01: boot sector , 0x02: first sector available
	mov ch, 0x00    ; 00 cylinder
    mov dh, 0x00    ; 0 head
    int 0x13        ;BIOS interrupt
    jc disk_error   ; if error
    pop dx
    cmp al, dh      ;check if sectors is right. Compare to the al value that BIOS issue.
    jne sectors_error
    popa
    ret

 disk_error:
	mov bx, error
	call print
	call printnl
	mov dh, ah
	call printhex
	jmp disk_loop

 sectors_error:
	mov bx, error
	call print
 disk_loop:
 	jmp $

error db "Error Exists, try again",0
