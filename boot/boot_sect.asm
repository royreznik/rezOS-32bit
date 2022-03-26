; Bios loads MBR into 0x7C00, so we want to look from there
[org 0x7c00]

mov [BOOT_DISK], dl  ; store the current first disk in variable
mov bp, 0x9000 ; The stack address
mov sp, bp ; if the stack is empty, sp is bp

mov bx, REAL_MODE_MSG
call print

call switch_to_pm

jmp $  ; This line will never be executed after switch_to_pm



%include "boot_print.asm"
%include "pm/print.asm"
%include "pm/gdt.asm"
%include "pm/switch.asm"


[bits 32]
BEGIN_PM:
    mov ebx, PROT_MODE_MSG
    call pm_print_string
    jmp $


BOOT_DISK: db 0 ; Just a variable  of the first disk


REAL_MODE_MSG db "Starting in 16-bit real mode", 0
PROT_MODE_MSG db "Loaded 32-bit protected mode", 0



; $ - the currnet address
; $$ - the first address
; write 510-(current addres - first address) of 0's
times 510-($-$$) db 0
; Magic number so the bios know its a bootable disk
dw 0xaa55