[bits 16]
[org 0x7c00]
mov bp, 0xC0C0
mov sp, bp

;print open screen message
push open_message
call print
add sp, 2

;enter into protected mode
call enter_protected_node

jmp $

%include "protected_mode.asm"
%include "gdt.asm"
%include "disk_16bit.asm"
%include "helper_16bit.asm"

open_message: db 'Penguin-OS', 0

TIMES 510-($-$$) db 0
dw 0xaa55