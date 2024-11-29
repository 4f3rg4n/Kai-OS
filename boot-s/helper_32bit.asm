[bits 32]
print_32bit:
    push ebx
    push edx
    push ebp
    mov ebp, esp

    mov ah , 0x0f
    mov edx , 0xb8000

    print_flow_32bit:
        mov al , byte [ebx]
        cmp al , 0 
        je stop_print_32bit

        mov [edx] , ax
        
        inc ebx
        add edx , 2 
        jmp print_flow_32bit

    stop_print_32bit:

    mov esp, ebp
    pop ebp
    pop edx
    pop ebx
    ret