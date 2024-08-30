[bits 32]

global isr_stub
extern isr_handler

tmp dw 0          ; Change to 32-bit
entry dw 0        ; Change to 32-bit

isr_stub:
    
    mov [tmp], eax          ; Save eax (32-bit)
    mov eax, [esp + 4]      ; Load interrupt number (32-bit)
    mov [entry], eax        ; Store interrupt number
    mov eax, [tmp]          ; Restore original eax

    pusha                   ; Push all general-purpose registers
    push ds                 ; Save segment registers
    push es
    push fs
    push gs
    mov ax, 0x10          
    mov ds, ax              
    mov es, ax             
    mov fs, ax           
    mov gs, ax              

    mov eax, [entry]        ; Load interrupt number (32-bit)
    push eax                ; Push it onto the stack

    call isr_handler        ; Call the C handler
    add esp, 4             ; Clean up the stack

    pop gs             
    pop fs
    pop es
    pop ds
    popa                
    
    ret             
    
