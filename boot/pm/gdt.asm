; Protected mode is 32 bit, allow as paging and multitasking, also allow as to use C
; GDT stars for Global descriptor table
; This is how we going to manage out segmentation from now on
; We declare two types of segments, code, and data, which everyone has different flags.
; Also we are using Flat memory model.


gdt_start: ; Use this label for easily save it after the implementation

gdt_null: ; the GDT stars with a null 8-byte
    dd 0x0
    dd 0x0

; GDT for code segment
gdt_code:
    dw 0xffff ; segment length, also call the limit
    dw 0x0  ; 16 bits +
    db 0x0 ;  8 bits = 24, for the base
    db 10011010b  ; present, privilege (2bits), type, type flags  (4 bits)
                  ; present - is the segment in use
                  ; privilege - 2 bits determinate privileged (00 == "ring")
                  ; type - 1 if code segment else 0
                  ; type flags:
                    ; first bit - code - is this segment is code?
                    ; second bit - Confirming - is this code can can be run with lower privileged segment?
                    ; third bit - Readable - is the segment readable
                    ; fourth bit - accessed - managed by the cpu
    db 11001111b ; the other flags, and the last 4 bits of the limit
                 ; other flags:
                    ; first bit - Granualarity - if 1 limit is multiplied by 0x1000
                    ; second bit - is it 32 bit
                    ; third bit - is it 64 bit
                    ; fourth bit - AVL
    db 0x0 ; last 8 bits of the base

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b ; This bits are the same as code, but with few exceptions:
                    ; type flags:
                        ; second bit - means the direction, if it is 1, the segement growth downwards
                        ; third bit - Writable
    db 11001111b
    db 0x0

gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start