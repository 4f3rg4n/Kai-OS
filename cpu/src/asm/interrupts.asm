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
extern irq_stub

isr00:
    push dword 0
    jmp run_isr

isr01:
    push dword 1
    jmp run_isr

isr02:
    push dword 2
    jmp run_isr

isr03:
    push dword 3
    jmp run_isr
isr04:
    push dword 4
    jmp run_isr

isr05:
    push dword 5
    jmp run_isr
    
isr06:
    push dword 6
    jmp run_isr

isr07:
    push dword 7
    jmp run_isr

isr08:
    push dword 8
    jmp run_isr

isr09:
    push dword 9
    jmp run_isr
    
isr10:
    push dword 10
    jmp run_isr

isr11:
    push dword 11
    jmp run_isr

isr12:
    push dword 12
    jmp run_isr

isr13:
    push dword 13
    jmp run_isr
    
isr14:
    push dword 14
    jmp run_isr

isr15:
    push dword 15
    jmp run_isr
        
isr16:
    push dword 16
    jmp run_isr

isr17:
    push dword 17
    jmp run_isr

isr18:
    push dword 18
    jmp run_isr

isr19:
    push dword 19
    jmp run_isr
    
isr20:
    push dword 20
    jmp run_isr

isr21:
    push dword 21
    jmp run_isr

isr22:
    push dword 22
    jmp run_isr
    
isr23:
    push dword 23
    jmp run_isr

isr24:
    push dword 24
    jmp run_isr

isr25:
    push dword 25
    jmp run_isr
    
isr26:
    push dword 26
    jmp run_isr

isr27:
    push dword 27
    jmp run_isr

isr28:
    push dword 28
    jmp run_isr
    
isr29:
    push dword 29
    jmp run_isr

isr30:
    push dword 30
    jmp run_isr

isr31:
    push dword 31
    jmp run_isr

irq00:
    push dword 32
    jmp run_irq

irq01:
    push dword 33
    jmp run_irq

irq02:
    push dword 34
    jmp run_irq

irq03:
    push dword 35
    jmp run_irq

irq04:
    push dword 36
    jmp run_irq

irq05:
    push dword 37
    jmp run_irq

irq06:
    push dword 38
    jmp run_irq

irq07:
    push dword 39
    jmp run_irq

irq08:
    push dword 40
    jmp run_irq

irq09:
    push dword 41
    jmp run_irq

irq10:
    push dword 42
    jmp run_irq

irq11:
    push dword 43
    jmp run_irq

irq12:
    push dword 44
    jmp run_irq

irq13:
    push dword 45
    jmp run_irq

irq14:
    push dword 46
    jmp run_irq

irq15:
    push dword 47
    jmp run_irq

run_isr:
    call isr_stub
    add esp, 4
    ret

run_irq:
    call irq_stub
    add esp, 4
    ret