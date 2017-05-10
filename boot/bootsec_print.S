; ASCII TABLE:
; 00:NULL         0B-2F: Special Sign and Icons
; 01-06: :)       30-39: 0-9
; 07: beep        3A-40: Question Marks/Quotations
; 08: back        41-46: A-F
; 09: tab         ......
; 0A: newline
;     
; i.e. 0x0A = Enter , Add 30H to display numbers !

;We have the following functions here:
;print --printing any strings
;printnl -- print a new line in tty mode
;printhex -- print a hexadecimal letter

print:
	pusha      ;keep all the values by pushing stack, prevent loosing them
	           ;數據結構中的堆棧操作

printloop:
	mov al, [bx]   ;bx is base address for the string. this operation gets content from address of bx
	cmp al, 0
	jz reachend

	               ;bios 0x0e print function
	mov ah, 0x0e
	int 0x10       ;char is being put to al by 'mov al, [bx]'
	inc bx
	jmp printloop

reachend:
	popa
	ret            ;i.e. return 0


printnl:
	pusha
	mov ah, 0x0e   ;14號功能
	mov al, 0x0A   ;See ascii table
	int 0x10
	mov al, 0x0d   ; carriage return
	int 0x10 

	popa
	ret

printhex:
	pusha
	mov cx, 0      ;A hex number has 4 digits, repeat 4 times to display a hex number
hexloop:
	cmp cx, 4
	jz hexend
	mov ax, dx     ;Calculate always happens in ax register, you dont want to lost the original data, do you?
	and ax, 0fh    ;tricks happens here. We get the last number of the digit. i.e. 0x1234-> 0x0004
	add al, 0x30    ;Add 30h to get the numbers in ascii. Check ascii table
	cmp al, 0x39
	jle next
	add al, 0x07

next:
	mov bx, HEXOUT+5
	sub bx, cx
	mov [bx], al
	ror dx, 4
	inc cx
	jmp hexloop

hexend:
    mov bx, HEXOUT   ;Before we call print function, we put parameters in bx
    call print

    popa
    ret

HEXOUT:
db  '0x0000', 0    ;Transitional memory for storage