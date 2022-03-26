[bits 32] ; using 32-bit protected mode

; Define some consts
VIDEO_MEMORY equ 0xb8000 ; the default
WHITE_ON_BLACK equ 0x0f ; the color bytes for each character

pm_print_string:
    pusha
    mov edx, VIDEO_MEMORY

    pm_print_string_loop:
        mov al, [ebx] ; ebx is the start of our string
        mov ah, WHITE_ON_BLACK ; set the color

        cmp al, 0; check if the string is ended
        je pm_print_string_done

        mov [edx], ax ; storage the character and the color into the screen
        inc ebx ; move to the next character
        add edx, 2 ; move 2 spaces because of the color byte

        jmp pm_print_string_loop


    pm_print_string_done:
        popa
        ret
