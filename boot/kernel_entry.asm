global _start;
[bits 32]

_start:
    [extern kmain] ; kmain is the first c function we calling in the kernel
    call kmain
    jmp $
