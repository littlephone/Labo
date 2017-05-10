[extern isr_handler] ;Tell the system to find this function in isr.c
[extern irq_handler]

;ISR code below
isr_general:
;1. Save CPU State by pushing to stack
   pusha  ;Push edi, esi, ebp, esp, eax, ebx, ecx, edx. (Protection)
   mov ax, ds  ;Save data segment
   push eax    ;to Stack via EAX
   mov ax, 0x10  ; kernel ds descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

;2. Call C handler
   call isr_handler

;3. Resore register state
   pop eax  ;Restore the value to eax
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   popa
   add esp, 8    ;Cleans the push ISR code and pushed number
   sti
   iret          ;Pop 5 things all together CS, EIP, EFLAGS, SS, ESP

;The following will be general instructions of IRQ
irq_general:
;1. Save CPU State by pushing to stack
   pusha  ;Push edi, esi, ebp, esp, eax, ebx, ecx, edx. (Protection)
   mov ax, ds  ;Save data segment
   push eax    ;to Stack via EAX
   mov ax, 0x10  ; kernel ds descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

;2. Call C handler
   call irq_handler

;3. Resore register state
   pop ebx  ;Restore the value to ebx
   mov ds, bx    ;We should pop ds, es, fs, gs to bx NOT AX
   mov es, bx
   mov fs, bx
   mov gs, bx
   popa
   add esp, 8    ;Cleans the push ISR code and pushed number
   sti
   iret          ;Pop 5 things all together CS, EIP, EFLAGS, SS, ESP


;The following functions is used to get the ISR from the computer
;So we just need to broadcast them :)
;I know, it's just way too like java :)
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

;IRQ
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15



;According to API, we define the different ISR as following:
;We push zero first if there's no error message
isr0:    ; 0: Divide by Zero Exception
   cli
   push byte 0
   push byte 0
   jmp isr_general

isr1:    ; 1.Debug Exception
   cli
   push byte 0
   push byte 1
   jmp isr_general

isr2:    ; 2. Non maskable interrupt exception
   cli
   push byte 0
   push byte 2
   jmp isr_general

isr3:    ; 3. Int 3 Exception
   cli
   push byte 0
   push byte 3
   jmp isr_general

isr4:    ; 4. INTO Exception
   cli
   push byte 0
   push byte 4
   jmp isr_general

isr5:    ; 5. Out of bounds Exception
   cli
   push byte 0
   push byte 5
   jmp isr_general

isr6:    ; 6. Invalid Opcode Exception
   cli
   push byte 0
   push byte 6
   jmp isr_general

isr7:    ; 7. Coprocessor Not Avail Jackpot
   cli
   push byte 0
   push byte 7
   jmp isr_general

isr8:    ; 8. Double Fault (With ERR CODE)
   cli
   push byte 8
   jmp isr_general

isr9:    ; 9. Coprocessor Segment Overrun
   cli
   push byte 0
   push byte 9
   jmp isr_general

isr10:
   cli    ;10. Bad TSS
   push byte 10
   jmp isr_general

isr11:    ;11. Segment Not Present Exception
   cli  
   push byte 11
   jmp isr_general

isr12:    ;12. Stack Fault Exception
   cli
   push byte 12
   jmp isr_general

isr13:    ;13. General Protection Fault Exception
   cli
   push byte 13
   jmp isr_general

isr14:    ;14. Page Fault Exception
   cli
   push byte 14
   jmp isr_general

isr15:    ;15. Reserved Exception
   cli
   push byte 0
   push byte 15
   jmp isr_general

isr16:    ;16. Floating Point Exception
   cli
   push byte 0
   push byte 16
   jmp isr_general

isr17:    ;17. Alignment Check Exception
   cli
   push byte 0
   push byte 17
   jmp isr_general

isr18:    ;18. Machine Check Exception
   cli
   push byte 0
   push byte 18
   jmp isr_general

isr19:    ;19-31: Those are reserved
   cli
   push byte 0
   push byte 19
   jmp isr_general

isr20:    ;If they are being used, just write specific code
   cli
   push byte 0
   push byte 20
   jmp isr_general

isr21:
   cli
   push byte 0
   push byte 21
   jmp isr_general

isr22:
   cli
   push byte 0
   push byte 22
   jmp isr_general

isr23:
   cli
   push byte 0
   push byte 23
   jmp isr_general

isr24:
   cli
   push byte 0
   push byte 24
   jmp isr_general

isr25:
   cli
   push byte 0
   push byte 25
   jmp isr_general

isr26:
   cli
   push byte 0
   push byte 26
   jmp isr_general

isr27:
   cli
   push byte 0
   push byte 27
   jmp isr_general

isr28:
   cli
   push byte 0
   push byte 28
   jmp isr_general

isr29:
   cli
   push byte 0
   push byte 29
   jmp isr_general

isr30:
   cli
   push byte 0
   push byte 30
   jmp isr_general

isr31:
   cli
   push byte 0
   push byte 31
   jmp isr_general

;------------------IrQ handler------------------
irq0:
   cli
   push byte 0
   push byte 32
   jmp irq_general

irq1:
   cli
   push byte 1
   push byte 33
   jmp irq_general

irq2:
   cli
   push byte 2
   push byte 34
   jmp irq_general

irq3:
   cli
   push byte 3
   push byte 35
   jmp irq_general

irq4:
   cli
   push byte 4
   push byte 36
   jmp irq_general

irq5:
   cli
   push byte 5
   push byte 37
   jmp irq_general

irq6:
   cli
   push byte 6
   push byte 38
   jmp irq_general

irq7:
   cli
   push byte 7
   push byte 39
   jmp irq_general

irq8:
   cli
   push byte 8
   push byte 40
   jmp irq_general

irq9:
   cli
   push byte 9
   push byte 41
   jmp irq_general

irq10:
   cli
   push byte 10
   push byte 42
   jmp irq_general

irq11:
   cli
   push byte 11
   push byte 43
   jmp irq_general

irq12:
   cli
   push byte 12
   push byte 44
   jmp irq_general

irq13:
   cli
   push byte 13
   push byte 45
   jmp irq_general

irq14:
   cli
   push byte 14
   push byte 46
   jmp irq_general

irq15:
   cli
   push byte 15
   push byte 47
   jmp irq_general
