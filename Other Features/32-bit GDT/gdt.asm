;GDT - Global Descriptor
gdt_start:

    ;This descriptor is empty and has only null bytes
    null_descriptor:
        dd 0
        dd 0

    ;This descriptor use for code
    code_desc:
        dw 0xffff    ;Descriptor limit size

        dw 0         ;Start of descriptor address 3-bytes
        db 0           
                     ; Flags settings:
                     ; ---------------------------------------------------------------------------------------------------------------
        db 10011010b ;|First 4 bits:  1-bit present = 1      |2-bit privilage = 00   |1-bit codedata(1) or traps(0) = 1               |
                     ;|--------------------------------------|-----------------------|------------------------------------------------|
                     ;|Second 4 bits: 1-bit contains code = 1|1-bit is conforming = 0|1-bit is readable = 1|Accessed = 0 (cpu bit...) |
                     ; ---------------------------------------------------------------------------------------------------------------

                     ; Flags settings:
                     ; ------------------------------------------------------------------------------------------------------------------------------
        db 11001111b ;|One byte: 1-bit Granularity = 1|1-bit 32 bit code = 1|1-bit is64? = 0|1-bit Userbit = 0|4-bit segment limit 4 more bits = 1111|
                     ; ------------------------------------------------------------------------------------------------------------------------------

        db 0         ;End ofdescriptor addres 1-byte

    ;This descriptor use for data
    data_desc:
        dw 0xffff    ;Descriptor limit size

        dw 0         ;Start of descriptor address 3-bytes
        db 0           
                     ; Flags settings:
                     ; ---------------------------------------------------------------------------------------------------------------
        db 10010010b ;|First 4 bits:  1-bit present = 1      |2-bit privilage = 00   |1-bit codedata(1) or traps(0) = 1               |
                     ;|--------------------------------------|-----------------------|------------------------------------------------|
                     ;|Second 4 bits: 1-bit contains code = 0|1-bit is direction = 0 |1-bit is writeable = 1|Accessed = 0 (cpu bit...)|
                     ; ---------------------------------------------------------------------------------------------------------------

                     ; Flags settings:
                     ; ------------------------------------------------------------------------------------------------------------------------------
        db 11001111b ;|One byte: 1-bit Granularity = 1|1-bit 32 bit code = 1|1-bit is64? = 0|1-bit Userbit = 0|4-bit segment limit 4 more bits = 1111|
                     ; ------------------------------------------------------------------------------------------------------------------------------

        db 0         ;End ofdescriptor addres 1-byte

gdt_end:

;GDT descriptor
gdt_descriptor:
    dw gdt_start - gdt_end - 1 ;GDT size
    dd gdt_start               ;GDT start address

CODE_SEG equ code_desc - gdt_start
DATA_SEG equ data_desc - gdt_start