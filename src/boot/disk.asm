;This function get dest address to store data from the disk, start sector & num of sectors to read,
;and it store the data from that sectors in the dest address.
disk_read:
    push bx
    push cx
    push dx
    push bp
    mov bp, sp

    mov bx, [bp + 14]  ;data store address
    mov ah, 2         ;read mode
    mov al, byte [bp + 12] ;num of sectors to read
    mov cl, byte [bp + 10] ;start sector
    mov ch, 0         ;cylinder num %
    mov dh, 0         ;cylinder num %
    int 0x13

    jc disk_error

    cmp al, byte [bp + 12]
    jne read_error

    jmp read_end

    ;unable to read from disk
    disk_error:
        push disk_error_msg
        call print
        add sp, 2
        jmp read_end

    ;not read all sectors
    read_error:
        push read_error_msg
        call print
        add sp, 2
        jmp read_end


    read_end:
        mov sp, bp
        pop bp
        pop dx
        pop cx
        pop bx
        ret

disk_error_msg: db "ERROR: Disk read faild", 0
read_error_msg: db "ERROR: Cannot finish disk read", 0
