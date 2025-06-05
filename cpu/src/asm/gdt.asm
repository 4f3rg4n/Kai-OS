[bits 32]

global reload_segments

reload_segments:
    ;jmp $
    mov ax, [esp + 4]; get struct gdt_entry ptr  (gdt_entry* entry)
    mov ebx, 0xb8000
    mov ax, ds
    add ax, 0x61
    mov [ebx], ax
    mov byte [ebx + 1], 0x0f
    jmp $
    ;mov ax, [ebx + 2] ; get base low (entry->base_low)

    mov ds , ax
    mov ss , ax 
    mov es , ax
    mov fs , ax
    mov gs , ax
    jmp flush ; flush cs

flush:
    ret