[BITS 16]
[ORG 0x7C00]
;/-----------------------\
;| start of boot sector  |
;\-----------------------/
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
    mov [BOOT_DRIVE], dl ;save boot drive addr

    ;print boot message
    push open_message
    call print_16bit
    add sp, 2
    
    mov bx, 0x7E00
    mov dh, 1 ;num of sectors by kernel size
    mov dl, [BOOT_DRIVE]
    call disk_read

    ;switch to protected mode
    call switch_to_pm

    jmp $

%include "boot/disk_16bit.asm"
%include "boot/protected_mode.asm"
%include "boot/long_mode.asm"
%include "boot/gdt.asm"
%include "boot/helper_16bit.asm"
%include "boot/helper_32bit.asm"

open_message: db 'Start booting Kai-OS...', 0
BOOT_DRIVE: db 0x80

TIMES 510-($-$$) db 0
dw 0xAA55

;/-----------------------------------------\
;| start of protected & long modes sector  |
;\-----------------------------------------/
%include "boot/paging.asm"

[BITS 32]
protected_mode:
    mov ebx, PM_MSG
    call print_32bit
    
    jmp init_pt_protected
cont:
    mov ebx, PM_MSG
    call print_32bit
    call switch_to_lm
    jmp $ ;HLT

[BITS 64]
long_mode:
    mov ebx, LM_MSG
    call print_32bit

    call load_kernel
    jmp $ ;HLT

[BITS 64]
load_kernel:
    call KERNEL_LOCARION
    jmp $ ;HLT

KERNEL_LOCARION equ 0x8200000

PM_MSG: db 'Entered into protected mode', 0
LM_MSG: db 'Entered into long mode', 0
times 512 - ($ - protected_mode) db 0x00 ;end of sector
;/-----------------------------------------\
;|      start of paging tables sector      |
;\-----------------------------------------/
[BITS 32]
paging_sector:
pml4_table db 0x1000  ; PML4 table, initialized with zeros (4 KB)
pdp_table db 0x1000   ; PDPT table, initialized with zeros (4 KB)
pd_table db 0x1000    ; PD table, initialized with zeros (4 KB)
pt_table db 0x1000    ; PT table, initialized with zeros (4 KB)
times 512 - ($ - paging_sector) db 0x00 ;end of sector