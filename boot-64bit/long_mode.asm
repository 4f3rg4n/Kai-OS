[bits 32]
global enable_long_mode
extern kmain
section .bss
align 4096
pml4_lbl: resq 512 ; PML4 table

section .text
enable_long_mode:
    ; Enable PAE in CR4
    ;mov eax, cr4
    ;or eax, 0x20 ; Set PAE bit (Physical Address Extension)
    ;mov cr4, eax

    ; Set Long Mode Enable (LME) in IA32_EFER MSR
    mov ecx, 0xC0000080 ; IA32_EFER MSR
    rdmsr ; Read MSR
    or eax, 0x100 ; Set LME bit
    wrmsr ; Write MSR

    ; Load Page Tables (PML4 base address must be set into CR3)
    ;mov eax, pml4_lbl ; Load the physical address of the PML4 table
    ;mov cr3, eax ; Set CR3 to point to the PML4 table

    ; Enable paging in CR0
    ;mov eax, cr0
    ;or eax, 0x80000000 ; Set PG (Paging) bit
    ;mov cr0, eax


    ; Jump to 64-bit mode
    jmp CODE_SEG_64_BIT:init_long_mode

[bits 64]
init_long_mode:
    ; Set up segment registers for 64-bit mode
    mov ax, DATA_SEG_64_BIT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Set up stack pointer
    mov rsp, 0x9000
    ;jmp $
    ; Call the 64-bit kernel entry point
    push LM_MSG
    call print_32bit
    jmp $

    ; Infinite loop to prevent returning
    hlt
