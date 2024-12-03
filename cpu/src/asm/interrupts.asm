[bits 32]

global isr00
global isr01
global isr02
global isr03
global isr04
global isr05
global isr06
global isr07
global isr08
global isr09
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global irq00
global irq01
global irq02
global irq03
global irq04
global irq05
global irq06
global irq07
global irq08
global irq09
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15


extern isr_stub

isr00:
    push dword 0
    jmp run

isr01:
    push dword 1
    jmp run

isr02:
    push dword 2
    jmp run

isr03:
    push dword 3
    jmp run
isr04:
    push dword 4
    jmp run

isr05:
    push dword 5
    jmp run
    
isr06:
    push dword 6
    jmp run

isr07:
    push dword 7
    jmp run

isr08:
    push dword 8
    jmp run

isr09:
    push dword 9
    jmp run
    
isr10:
    push dword 10
    jmp run

isr11:
    push dword 11
    jmp run

isr12:
    push dword 12
    jmp run

isr13:
    push dword 13
    jmp run
    
isr14:
    push dword 14
    jmp run

isr15:
    push dword 15
    jmp run
        
isr16:
    push dword 16
    jmp run

isr17:
    push dword 17
    jmp run

isr18:
    push dword 18
    jmp run

isr19:
    push dword 19
    jmp run
    
isr20:
    push dword 20
    jmp run

isr21:
    push dword 21
    jmp run

isr22:
    push dword 22
    jmp run
    
isr23:
    push dword 23
    jmp run

isr24:
    push dword 24
    jmp run

isr25:
    push dword 25
    jmp run
    
isr26:
    push dword 26
    jmp run

isr27:
    push dword 27
    jmp run

isr28:
    push dword 28
    jmp run
    
isr29:
    push dword 29
    jmp run

isr30:
    push dword 30
    jmp run

isr31:
    push dword 31
    jmp run

run:
    call isr_stub
    add esp, 4
    ret