; infinite loop
loop:
    jmp loop


times 510-($-$$) db 0
; Magic number so the bios know its a bootable disk
dw 0xaa55