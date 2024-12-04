[bits 32]

global isr_stub
global irq_stub

extern isr_handler
extern irq_handler

tmp dw 0          
entry dw 0      

isr_stub:
    mov [tmp], eax          ; save eax (32-bit)
    mov eax, [esp + 4]      ; load interrupt number (32-bit)
    mov [entry], eax        ; store interrupt number
    mov eax, [tmp]          ; restore original eax

    pusha                  
    push ds                 ; save segment registers
    push es
    push fs
    push gs
    mov ax, 0x10          
    mov ds, ax              
    mov es, ax             
    mov fs, ax           
    mov gs, ax              

    mov eax, [entry]        ; load interrupt number (32-bit)
    push eax                ; push it onto the stack to pass it to the C function

    call isr_handler        ; call the C handler
    add esp, 4           

    pop gs             
    pop fs
    pop es
    pop ds
    popa                
    
    ret             
    
irq_stub:
    mov [tmp], eax          ; save eax (32-bit)
    mov eax, [esp + 4]      ; load interrupt number (32-bit)
    mov [entry], eax        ; store interrupt number
    mov eax, [tmp]          ; restore original eax

    pusha                  
    push ds                 ; save segment registers
    push es
    push fs
    push gs
    mov ax, 0x10          
    mov ds, ax              
    mov es, ax             
    mov fs, ax           
    mov gs, ax              

    mov eax, [entry]        ; load interrupt number (32-bit)
    push eax                ; push it onto the stack to pass it to the C function

    call irq_handler        ; call the C handler
    add esp, 4           

    pop gs             
    pop fs
    pop es
    pop ds
    popa                
    
    ret    