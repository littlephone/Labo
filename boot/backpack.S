gdtstart:
	;Backpack init. Null 8 bits
	dd 0x0
	dd 0x0

;GDT code segment. !Page 35
gdtcode:
	dw 0xffff       ;segment length, bits 0-15
	dw 0x0          ;segment base from bits 0-15
	db 0x0			;segment base from 16-23
	db 10011010b	;flags (8 bits)
	db 11001111b	;flags(4bit)+ segment length, bits 16-19
	db 0x0          ;segment base, bits 24-31

gdtdata:
        dw 0xffff       ;segment length, bits 0-15
	dw 0x0          ;segment base from bits 0-15
	db 0x0			;segment base from 16-23
	db 10010010b	;flags (8 bits)
	db 11001111b	;flags(4bit)+ segment length, bits 16-19
	db 0x0          ;segment base, bits 24-31

gdtend:

descriptor:
	dw gdtend-gdtstart-1	;size always =16 bit -1
	dd gdtstart 			;address(32 bit)

CODE_SEG equ gdtcode-gdtstart
DATA_SEG equ gdtdata-gdtstart
