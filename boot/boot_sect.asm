; Bios loads MBR into 0x7C00, so we want to look from there
[org 0x7c00]
KERNEL_LOCATION equ 0x1000
mov [BOOT_DISK], dl  ; store the current first disk in variable
mov bp, 0x8000 ; The stack address
mov sp, bp ; if the stack is empty, sp is bp

mov bx, REAL_MODE_MSG
call print

mov bx, LOAD_KERNEL_MSG
call print

; loads the kernel:
; Where we want to load our segments is determine by es:bx which is es * 16 + bx
mov bx, KERNEL_LOCATION
mov dh, 31
mov ah, 0x02 ; int 0x13 function, 0x02 = 'read'
mov al, dh ; how many sectors to read
mov ch, 0x00 ; The cylinder number
mov cl, 0x02 ; sector number
mov dh, 0x00 ; head number
mov dl, [BOOT_DISK] ; which disk to load from
int 0x13

; clear the screen after changing into text mode
mov ah, 0x0
mov al, 0x3
int 0x10

call switch_to_pm

jmp $  ; This line will never be executed after switch_to_pm



%include "boot/boot_print.asm"
%include "boot/pm/print.asm"
%include "boot/pm/gdt.asm"
%include "boot/pm/switch.asm"


[bits 32]
BEGIN_PM:
    jmp KERNEL_LOCATION
    jmp $


BOOT_DISK: db 0 ; Just a variable  of the first disk


REAL_MODE_MSG db "Starting in 16-bit real mode", 0
LOAD_KERNEL_MSG db "Loading kernel from disk", 0
PROT_MODE_MSG db "Loaded 32-bit protected mode", 0



; $ - the currnet address
; $$ - the first address
; write 510-(current addres - first address) of 0's
times 510-($-$$) db 0
; Magic number so the bios know its a bootable disk
dw 0xaa55