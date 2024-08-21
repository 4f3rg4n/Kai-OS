[BITS 32]
[ORG 0x2000]

_main:
    push ebx
    push ebp
    mov ebp, esp

    mov ebx, 0xb8000
    mov BYTE [ebx], 'R'

    jmp $
    
    mov esp, ebp
    pop ebp
    pop ebx
    ret