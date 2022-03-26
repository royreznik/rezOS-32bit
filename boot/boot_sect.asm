; Bios loads MBR into 0x7C00, so we want to look from there
[org 0x7c00]

mov [BOOT_DISK], dl  ; store the current first disk in variable
mov bx, HELLO
call print
mov bp, 0x9000 ; The stack address
mov sp, bp ; if the stack is empty, sp is bp
jmp $  ; infinite loop



%include "boot_print.asm"


BOOT_DISK: db 0 ; Just a variable  of the first disk


HELLO:
    db "Hello, World", 0


; $ - the currnet address
; $$ - the first address
; write 510-(current addres - first address) of 0's
times 510-($-$$) db 0
; Magic number so the bios know its a bootable disk
dw 0xaa55