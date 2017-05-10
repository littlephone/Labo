[bits 32]
[extern main]	;Define calling point to main in language c
call main    ;Call C function.The linker will know where it placed in memory
jmp $
