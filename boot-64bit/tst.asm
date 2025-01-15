/*
load_memory_map:
    ; Initialize buffer for memory map
    mov MEMORY_MAP_BUFFER
    xor ebx, ebx             ; Clear continuation value
    mov cx, 24               ; Size of the buffer
    mov edx, 0x534D4150      ; 'SMAP' magic value

memory_map_loop:
    mov eax, 0xE820          ; Function ID
    mov di, bx               ; ES:DI points to the buffer
    int 0x15                 ; BIOS call to get memory map
    jc memory_map_error      ; If carry flag is set, error occurred

    cmp eax, 0x534D4150      ; Check if 'SMAP' magic value is returned
    jne memory_map_error     ; If not, something went wrong

    ; Update buffer pointer to next position
    add bx, 24               ; Move to the next memory map entry
    test ebx, ebx            ; Check if continuation value is zero
    jnz memory_map_loop      ; If continuation value is non-zero, repeat the call

    ret                      ; Return once the memory map is fully loaded

memory_map_error:
    ; Print error and halt
    push mem_map_error_msg
    call print_16bit
    add sp, 2
    hlt

*/
MEMORY_MAP_BUFFER equ 0x5000

mem_map_error_msg: db 'Memory map error!', 0
