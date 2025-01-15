[bits 16]
;This function get string pointer and print it
print_16bit:
    push si
    push bp
    mov bp, sp

    mov ah, 0x0E ;tty
    mov si, [bp + 6]

    ;print until detect null byte
    print_flow_16bit:
        mov al, [si]
        cmp al, 0
        je stop_print_16bit                
        int 0x10
        inc si
        jmp print_flow_16bit

    ;when null byte
    stop_print_16bit:
        call new_line_16bit
        mov sp, bp
        pop bp
        pop si
        ret 
                
;This function enter to new write line                
new_line_16bit:
    mov ah, 0x0E ;tty
    mov al, 0x0A ;enter
    int 0x10
    mov al, 0x0D ;back to start of line
    int 0x10
    ret