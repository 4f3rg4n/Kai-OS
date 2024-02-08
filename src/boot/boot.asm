[BITS 16]
[ORG 0x7c00]

jmp $

TIMES 510-($-$$) db 0
dw 0xaa55