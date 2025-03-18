[BITS 32]
disk_read_pm:
    pusha

    call ata_pio_read        ; Read from disk using PIO mode

    popa
    ret

; ATA PIO Disk Read Function (Protected Mode)
ata_pio_read:
    pusha

    mov dx, 0x1F2    ; Sector count port
    mov al, cl       ; Number of sectors to read
    out dx, al

    mov dx, 0x1F3    ; LBA low byte
    mov al, 2        ; Start at sector 2 (assuming first sector is bootloader)
    out dx, al

    mov dx, 0x1F4    ; LBA mid byte
    mov al, 0
    out dx, al

    mov dx, 0x1F5    ; LBA high byte
    mov al, 0
    out dx, al

    mov dx, 0x1F6    ; Drive & LBA mode
    mov al, 0x40 
    out dx, al

    mov dx, 0x1F7    ; Command port
    mov al, 0x20     ; Read sectors command
    out dx, al

    ; Read loop
.wait_bsy:
    in al, dx        ; Read status
    test al, 0x80    ; Check if BSY (Busy) is set
    jnz .wait_bsy    ; Wait until BSY clears

    test al, 0x01    ; Check ERR (Error) bit
    jnz .ata_error   ; If ERR is set, jump to error handler

.wait_drq:
    in al, dx        ; Read status again
    test al, 8       ; Check if DRQ (Data Request) is set
    jz .wait_drq     ; Wait until DRQ is set

    mov ecx, 256     ; 256 words per sector
.read_loop:
    mov dx, 0x1F0    ; Data port
    in ax, dx        ; Read word
    stosw           ; Store at [EDI]
    loop .read_loop

    popa
    ret

.ata_error:
    mov ebx, ata_err_msg
    call print_32bit
    jmp $

ata_err_msg: db "ERROR: ata read faild", 0