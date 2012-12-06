assume cs:code

code segment

start:
        mov ax,0
        mov ss,ax
        mov sp,4
        mov cx,2
        mov bx,0
        mov ax,cs
        mov ds,ax

b:
        pop ds:[bx]
        add bx,2
        loop b

        mov ax,4c00h
        int 21h

code ends

end start
