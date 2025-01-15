[BITS 16]
[ORG 0x7C00]
BIOS_Parametr_Block:
    jmp short boot_start

    ;OEM name (8 bytes)
    db "Kai-OS"         
    dw 0

    ;BPB data
    dw 512     ;bytes per sector
    db 1       ;sectors per cluster
    dw 1       ;reserved sectors
    db 2       ;number of FATs
    dw 224     ;maximum root directory entries
    dw 2880    ;total sectors
    db 0xF0    ;media descriptor
    dw 9       ;sectors per FAT
    dw 18      ;sectors per track
    dw 2       ;number of heads
    dd 0       ;hidden sectors
    dd 0       ;large total sectors

boot_start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov [BOOT_DRIVE], dl ;save boot drive addr

    ;open message
    a:
    push open_message
    call print_32bit
    add sp, 2
    jmp a
    ; Load GDT and switch to protected mode
    call switch_to_pm

    ; Infinite loop to prevent returning
    hlt

%include "boot/disk_16bit.asm"
%include "boot/protected_mode.asm"
%include "boot/long_mode.asm"   
%include "boot/gdt.asm"
%include "boot/helper_16bit.asm"
%include "boot/helper_32bit.asm"

times 510-($-$$) db 0
dw 0xAA55

section .bss
BOOT_DRIVE: resb 1
KERNEL_LOCATION equ 0x100000 ; 1MB
open_message: db 'Start booting Kai-OS...', 0
PM_MSG: db 'Entered into protected mode', 0
LM_MSG: db 'Entered into long mode', 0