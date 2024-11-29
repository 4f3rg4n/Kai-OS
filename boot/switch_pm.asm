[bits 16]
switch_to_pm:

    cli ;turn off interrups
    lgdt [gdt_descriptor] ;load GDT table

    ;set the control bit to 1    
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    call CODE_SEG:init_pm

[bits 32]
init_pm:
    ;set data seg registers to the data seg addr
    mov ax, DATA_SEG
    mov ds , ax
    mov ss , ax 
    mov es , ax
    mov fs , ax
    mov gs , ax

    ;init stack at 0x9000
    mov ebp, 0x9000
    mov esp, ebp

    ;start pm
    call BEGIN_PM
