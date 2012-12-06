assume cs:code

code segment

start:
        xor ax,ax
        mov al,41
        not al
        ;and al,01111111b
        add al,1

        mov ax,4c00h
        int 21h

code ends

end start
