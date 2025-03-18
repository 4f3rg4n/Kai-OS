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
    call enable_a20
    call unreal_mode
    ;call load_kernel
    call switch_to_pm

    jmp $

%include "boot/ata.asm"
%include "boot/protected_mode.asm"
%include "boot/gdt.asm"
%include "boot/helper_16bit.asm"
%include "boot/helper_32bit.asm"

[BITS 16]

enable_a20:
    push ax
    mov ax, 2401h
    int 15h   ; Enable A20 line
    pop ax
    ret

unreal_mode:    

	cli 		  ; Clear interrupts
	push ds		; Save segment

	lgdt [gdt_descriptor]	; Load Global Descriptor Table

	; Temporarily go to protected mode
	mov eax, cr0          
  or al, 1                
  mov cr0, eax

	jmp .continue   ; Clean pipe

.continue:

	mov  bx, 0x8         ; Select descriptor 1
	mov  ds, bx       

	; Back to real mode
	and al, 0FEh
	mov cr0, eax

	pop ds      ; Get back old segment
	sti					; Return interrupts

	ret


[BITS 32]
protected_mode:
    mov ebx, PM_MSG
    call print_32bit
    call load_kernel
    ;jmp $
    call KERNEL_LOCATION ; RUN KERNEL !!!
    mov ebx, PM_MSG
    call print_32bit
    jmp $ ;hlt

load_kernel:
    ;mov edi, KERNEL_LOCATION  ; Destination address (32-bit)
    ;mov ecx, 1              ; Number of sectors to read
    ;call disk_read_pm        ; Read kernel from disk
    mov ebx, 40
    mov ecx, 122h
    mov edi, KERNEL_LOCATION
    call ata_read_s
    ret

KERNEL_LOCATION equ 0x100000

open_message: db 'Start booting Kai-OS...', 0
PM_MSG: db 'Entered into protected mode', 0
BOOT_DRIVE: db 0x80

idts:
TIMES 510-($-$$) db 0
dw 0xaa55

;second_sect:
;%include "boot/disk_32bit.asm"
;TIMES 512-(second_sect-$$) db 0