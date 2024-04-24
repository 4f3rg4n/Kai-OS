[bits 16]
enter_protected_node:

    cli ;turn off interrups
    lgdt [GDT_descriptor] ;load GDT table

    ;set the control bit to 1    
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    call CODE_SEGMENT:init_protected_mode

[bits 32]
init_protected_mode:
    mov ax, DATA_SEGMENT
    mov ds , ax
    mov ss , ax 
    mov es , ax
    mov fs , ax
    mov gs , ax

    mov ebp, 0xC0C0C
    mov esp, ebp

    call start_protected_mode

start_protected_mode:
    jmp $