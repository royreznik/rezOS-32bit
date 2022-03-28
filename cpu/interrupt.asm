[EXTERN isr_handler]

; This is a common ISR stub, saves the processor state, sets up the kernel mode segments,
; call the C-level fault handler, and finally restore the stack frame.
isr_common_stub:
    pusha               ; Push edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds          ; Lower 16 bit of eax = ds.
    push eax            ; save the data segment descriptor

    mov ax, 0x10        ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax             ; Reload the original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs ,ax
    mov gs, ax

    popa                ; pops all
    add esp, 8          ; clean up the pushed error code and pushed isr number
    sti
    iret                ; pip 5 things at once, CS EIP EFLAGS SS, ESP



%macro ISR_NOERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli                     ; Disable interrupts
        push byte 0             ; Push dummy error code, as the fist 16 interrupts doesn't have one
        push byte %1            ; Push the interrupt number
        jmp isr_common_stub     ; call our common handler
%endmacro


%macro ISR_ERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

