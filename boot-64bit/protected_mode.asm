section .text
[bits 16]
global switch_to_pm

switch_to_pm:
    cli ; turn off interrupts
    lgdt [gdt_descriptor] ; load GDT table

    ; Enable protected mode
    mov eax, cr0
    or eax, 0x1 ; set PM (Protected Mode) bit
    mov cr0, eax

    jmp CODE_SEG_32_BIT:init_pm

[bits 32]
init_pm:
    ; Set data segment registers to the data segment address
    mov ax, DATA_SEG_32_BIT
    mov ds, ax
    mov ss, ax 
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Initialize stack at 0x9000
    mov ebp, 0x9000
    mov esp, ebp
    push PM_MSG
    call print_32bit
    add sp, 2
    jmp $

    ; Start long mode setup
    call enable_long_mode

    ; Infinite loop to prevent returning
    hlt
