[BITS 16]
[ORG 0x7C00]
boot_start:
    KERNEL_LOCARION equ 0x1000

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
    mov dh, 31 ;num of sectors by kernel size
    mov dl, [BOOT_DRIVE]
    call disk_read
    ret 

[BITS 32]
protected_mode:
    push PM_MSG
    call print_32bit
    add sp, 2

    call KERNEL_LOCARION ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns control to us (if ever)

open_message: db 'Start booting Kai-OS...', 0
PM_MSG: db 'Entered into protected mode', 0
BOOT_DRIVE: db 0

TIMES 510-($-$$) db 0
dw 0xaa55

