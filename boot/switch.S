[bits 16]    ;Still in 16-bit
switch_to_pm:
	cli						
	lgdt[descriptor]		
	mov eax, cr0
	or eax, 0x1             ;set 32-bit mode bit in cr0
	mov cr0, eax
	jmp CODE_SEG:init_pm    ;far jump by using a different segment
	                        ;cannot simply jump to init_pm due to limitation of near jump!

[bits 32]     ;32-bit protected mode ! Use 32 bit instrctions NOW
init_pm:
	mov ax, DATA_SEG        ;Update and initialize the segment registers
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000         ;Update Stack right at the top of free space
	mov esp, ebp             ;cannot give value to stack pointer directly, use ebp as transition

	call BEGIN_PM
