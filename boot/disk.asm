[bits 16]
;This function get dest address to store data from the disk, start sector & num of sectors to read,
;and it store the data from that sectors in the dest address.
disk_load:
    pusha
    push dx

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
