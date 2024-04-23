;This function get string pointer and print it
print:
    push si
    push bp
    mov bp, sp

    mov ah, 0x0e ; tty
    mov si, [bp + 6]

    print_flow:
        mov al, [si]
        cmp al, 0
        je stop_print                
        int 0x10
        inc si
        jmp print_flow

    stop_print:
        mov sp, bp
        pop bp
        pop si
        ret 
                