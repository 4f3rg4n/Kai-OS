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

push 0x1000
push 15
push 2
call disk_read
add sp, 6

call enter_protected_node

jmp $

%include "disk_16bit.asm"
%include "protected_mode.asm"
%include "gdt.asm"
%include "helper_16bit.asm"
%include "helper_32bit.asm"

open_message: db 'Penguin-OS', 0
RM_MSG: db 'Hello from Real Mode!', 0

TIMES 510-($-$$) db 0
dw 0xaa55
times 512 dw 0x61
times 512 dw 0x62