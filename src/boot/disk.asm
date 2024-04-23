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

    mov sp, bp
    pop bp
    pop dx
    pop cx
    pop bx
    ret