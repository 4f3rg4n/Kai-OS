[bits 16]
[org 0x7c00]
mov bp, 0xC0C0
mov sp, bp

;print open screen message
push open_message
call print_16bit
add sp, 2
call new_line_16bit
push RM_MSG
call print_16bit
add sp, 2
call new_line_16bit

;enter into protected mode
call enter_protected_node

jmp $

%include "protected_mode.asm"
%include "gdt.asm"
%include "disk_16bit.asm"
%include "helper_16bit.asm"
%include "helper_32bit.asm"
open_message: db 'Penguin-OS', 0
RM_MSG: db 'Hello from Real Mode!', 0

TIMES 510-($-$$) db 0
dw 0xaa55