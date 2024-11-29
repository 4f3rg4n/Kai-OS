BITS 32

;Multiboot standard

SECTION .text
    align   4
    dd      0x1BADB002          ; header id magic flag
    dd      0x00                ; Flags
    dd      - (0x1BADB002+0x00) ; Checksum

GLOBAL start
EXTERN kmain

start:
    cli                 
    call kmain ;start kernel main func
    jmp $