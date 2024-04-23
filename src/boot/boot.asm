[BITS 16]
[ORG 0x7c00]
mov bp, 0xC0C0
mov sp, bp

;print open screen message
push open_message
call print
add sp, 2

jmp $

open_message: db 'Penguin-OS', 0

%include "disk.asm"
%include "helper.asm"

TIMES 510-($-$$) db 0
dw 0xaa55
