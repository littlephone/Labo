; Labo 2017 , Chow Raynold  2017 (C) All rights reserved
; Last modified: 2017/4/15
; 
; Package: Labo Base
; Version: 17.4.15- Labo BRANCH
;
; You might edit this file. But pay full attention to the instructions
; Instructions: 
; 1. This file is being used to boot the Laboratory.
; Modify with care. Because error in this file will render
; the system unbootable and unusable ! 
; 2. I appreciate everyone who attempts to read this file.
; Because a courage like this is a brand new start !
; 3. Let;s get started !
; 4. This file is ONLY FOR MAIN BRANCH , RELEASING THIS BOOTLOADER 
; TO ANDROID BRANCH WILL BRICK THE DEVICE. Well, you can try it if you
; have the courage to experience bootloop and kernel panic :)
; 5. I think you can join us if you are interested in editing and reading this file
; contact us at admin@labstry.com


; The OS always start from booting in address 0x7c00
; The BIOS sets us the boot drive while boot in dl.
org 0x7c00

	KERNEL_OFFSET equ 0x1000    ;Same as we used to link the kernel
	mov [DRIVE], dl;    ; Get the boot drive in dl, store to memory prevent getting lose
	mov bp, 0x9000      ;set stack away from us, its dangerous otherwise.
	mov sp, bp          ; cannot give value directly to sp, use bp as transition
	mov bx, BASEINFO    ; display info for base app
	call print          ;print cc message
	call printnl

	call loadkernel     ;read kernel from disks
	call switch_to_pm
	jmp $               ;wont execute

 %include "boot/bootsec_print.S"
 %include "boot/32bit-print.S"
 %include "boot/switch.S"
 %include "boot/backpack.S"
 %include "boot/disk.S"
 
[bits 16]
loadkernel:
	mov bx, MSG_LOAD_KERNEL
	call print
	call printnl
  ; The above message hints that the kernel is being loaded
  	mov bx, KERNEL_OFFSET    ;read from disk and store in 0x1000
  	mov dh, 51               ;read more sectors 
  	mov dl, [DRIVE]
  	call diskload
	mov bx, KERNEL_LOADED
	call print
	call printnl
  	ret

[bits 32]
BEGIN_PM:
	mov ebx, PROTECT
	call print_string_pm
	jmp  0x1000     ;See asm2c.S
	jmp $

DRIVE db 0   ;Store the bootdrive into memory
BASEINFO db "Labo Base - 17.4.15 , All Rights Reserved", 0
PROTECT db "Labo 17.4.15 Unstable", 0
MSG_LOAD_KERNEL db "Loading kernel...", 0
KERNEL_LOADED db "Kernel loaded sucessfully!", 0


;fill zero and Magic boot number
RESB 510-($-$$)
dw 0xaa55
