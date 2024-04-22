[BITS 16]
[ORG 0x7c00]

mov ah, 0x0e
mov al, 'N'
int 0x10
mov al, 'A'
int 0x10
mov al, 'p'
int 0x10
mov al, 'e'
int 0x10
mov al, 'n'
int 0x10
mov al, 'g'
int 0x10
mov al, 'u'
int 0x10
mov al, 'i'
int 0x10
mov al, 'n'
int 0x10
mov al, '-'
int 0x10
mov al, 'O'
int 0x10
mov al, 'S'
int 0x10
mov al, '.'
int 0x10
int 0x10
int 0x10

jmp $

TIMES 510-($-$$) db 0
dw 0xaa55