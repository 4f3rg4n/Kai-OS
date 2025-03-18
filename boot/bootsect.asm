[BITS 16]
[ORG 0x7C00]

;Note: BPB Struct can be found inside the kernel fs code file.
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

    call load_kernel
    call switch_to_pm

    jmp $

%include "boot/disk_16bit.asm"
%include "boot/protected_mode.asm"
%include "boot/gdt.asm"
%include "boot/helper_16bit.asm"
%include "boot/helper_32bit.asm"

[BITS 16]
load_kernel:
    mov bx, KERNEL_LOCARION  ;kernel entry
    mov dh, 64 ;num of sectors by kernel size
    mov dl, [BOOT_DRIVE]
    call disk_read
    ret 

[BITS 32]
protected_mode:
    mov ebx, PM_MSG
    call print_32bit
    ;jmp $
    call KERNEL_LOCARION ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns control to us (if ever)

KERNEL_LOCARION equ 0x8000

open_message: db 'Start booting Kai-OS...', 0
PM_MSG: db 'Entered into protected mode', 0
BOOT_DRIVE: db 0x80

TIMES 510-($-$$) db 0
dw 0xaa55
