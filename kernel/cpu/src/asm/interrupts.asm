[bits 32]

global isr0
global isr1

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

run:
    call isr_stub
    add esp, 4
    ret