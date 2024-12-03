[bits 16]
;This function get dest address to store data from the disk, start sector & num of sectors to read,
;and it store the data from that sectors in the dest address.
disk_read:
    pusha
    push dx

    ;mov ah, 0x02          ; BIOS read function
    ;mov al, 17             ; Number of sectors to read (1 sector)
    ;mov dl, 0x02          ; Disk drive number (0x80 = CD/DVD)
    ;mov ch, 0             ; Cylinder number (0)
    ;mov cl, 2             ; Sector number (sector 2)
    ;mov dh, 0             ; Head number (0 for CD)
    ;int 0x13  

    mov ah, 2         ;read mode
    mov al, dh ;num of sectors to read
    mov cl, byte 0x02
    mov ch, 0         ;cylinder num %
    mov dh, 0         ;cylinder num %
    int 0x13

    jc disk_error ;Cant open the disk sector for read

    pop dx
    cmp al, dh
    jne read_error ;Error while reading sectors

    jmp read_end

    ;unable to read from disk
    disk_error:
        push disk_error_msg
        call print_16bit
        add sp, 2
        jmp read_end

    ;not read all sectors
    read_error:
        push read_error_msg
        call print_16bit
        add sp, 2
        jmp read_end

    read_end:
        popa
        ret


disk_error_msg: db "ERROR: Disk read faild", 0
read_error_msg: db "ERROR: Cannot finish disk read", 0
