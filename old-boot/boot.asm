[BITS 16]
[ORG 0x7C00]
KERNEL_LOCARION equ 0x1000
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

push KERNEL_LOCARION
push 15
push 2
call disk_read
add sp, 6

mov bx, KERNEL_LOCARION  ;data store address
mov ah, 2         ;read mode
mov al, 15 ;num of sectors to read
mov cl, 2 ;start sector
mov ch, 0         ;cylinder num %
mov dh, 0         ;cylinder num %
int 0x13

call enter_protected_mode

jmp $

%include "disk_16bit.asm"
%include "protected_mode.asm"
%include "gdt.asm"
%include "helper_16bit.asm"
%include "helper_32bit.asm"

[BITS 32]
protected_mode:
EXTERN _start
    ;mov ebx, PM_MSG
    ;call print_32bit
    call _start

    ;call

    jmp $

;%include "kernel.asm"
open_message: db 'Penguin-OS', 0
RM_MSG: db 'Hello from Real Mode!', 0

TIMES 510-($-$$) db 0
dw 0xaa55

