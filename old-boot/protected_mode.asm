[bits 16]
enter_protected_mode:

    cli ;turn off interrups
    lgdt [GDT_descriptor] ;load GDT table

    ;set the control bit to 1    
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    call CODE_SEGMENT:init_protected_mode
    ret

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
    ret

start_protected_mode:
    ;call 0x1000
    call protected_mode
    
    ret

PM_MSG: db "Hello from Protected Mode !", 0