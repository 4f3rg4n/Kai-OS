[bits 32]
switch_to_lm:
    ;elevate to 64-bit mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    
    ;enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    
    call CODE_SEG_64_BIT:init_lm

[bits 64]
init_lm:
    ;set data seg registers to the data seg addr
    mov ax, DATA_SEG_64_BIT
    mov ds , ax
    mov ss , ax 
    mov es , ax
    mov fs , ax
    mov gs , ax

    ;start lm
    call long_mode
