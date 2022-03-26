; Bios loads MBR into 0x7C00, so we want to look from there
[org 0x7c00]
    mov bp, 0x8000 ; The stack address
    mov sp, bp ; if the stack is empty, sp is bp
    jmp $  ; infinite loop


; $ - the currnet address
; $$ - the first address
; write 510-(current addres - first address) of 0's
times 510-($-$$) db 0
; Magic number so the bios know its a bootable disk
dw 0xaa55