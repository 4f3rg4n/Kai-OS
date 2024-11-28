[bits 32]

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
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

extern isr_stub

isr0:
    push dword 0
    jmp run

isr1:
    push dword 1
    jmp run

isr2:
    push dword 2
    jmp run

isr3:
    push dword 3
    jmp run
isr4:
    push dword 4
    jmp run

isr5:
    push dword 5
    jmp run
    
isr6:
    push dword 6
    jmp run

isr7:
    push dword 7
    jmp run

isr8:
    push dword 8
    jmp run

isr9:
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