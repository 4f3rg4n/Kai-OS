[bits 32]

; Initialize the page table
init_pt_protected:
    
    ;pushad

    ; Clear the memory area using rep stosd
    mov edi, pml4_table
    xor eax, eax
    mov ecx, 512
    rep stosd

    ; Set edi back to PML4T[0]
    mov edi, pml4_table

    ; Set up the first entry of each table
    mov ebx, pdp_table
    or ebx, 0x3                          ; Set the flags to 0x0003
    mov dword [edi], ebx                 ; Set PML4T[0] to address of PDPT with flags 0x0003

    mov edi, pdp_table                    ; Go to PDPT[0]
    mov ebx, pd_table
    or ebx, 0x3                          ; Set the flags to 0x0003
    mov dword [edi], ebx       ; Set PDPT[0] to address of PDT with flags 0x0003

    mov edi, pd_table                     ; Go to PDT[0]
    mov ebx, pt_table
    or ebx, 0x3                          ; Set the flags to 0x0003
    mov dword [edi], ebx       ; Set PDT[0] to address of PT with flags 0x0003

    ; Fill in the final page table
    mov edi, pt_table                     ; Go to PT[0]
    mov ebx, 0x00000003                   ; EBX has address 0x0000 with flags 0x0003
    mov ecx, 512                          ; Do the operation 512 times

    add_page_entry_protected:
        mov dword [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop add_page_entry_protected

    ; Set up PAE paging, but don't enable it quite yet
    mov eax, cr4
    or eax, 1 << 5                        ; Set the PAE-bit, which is the 5th bit
    mov cr4, eax

    ; Now we should have a page table that identities maps the lowest 2MB of physical memory into
    ; virtual memory!
    
    ;popad
    ;ret
    jmp cont

