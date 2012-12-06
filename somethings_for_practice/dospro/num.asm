assume cs:code,ss:stack,ds:data

data segment

	dw 4 dup (0)

data ends

stack segment

	dw 8 dup (0)

stack ends

code segment

start:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,16
	mov ah,0
	mov al,1
	mov bl,1
	mov bh,0
	mov si,0
	mov cx,100

	call get

	call set

	call display

	mov ax,4c00h
	int 21h

get:
	add ax,bx
	inc bl
	loop get
	mov ds:[si],ax
	ret

set:
	mov bx,ds:[si]
l:
	mov bh,al
	mov al,ah
	shl ah,1
	add ah,30h
	and al,11110000b
	add al,30h
	push ax
	mov ah,bl
	shl ah,1
	add ah,30h
	and al,11110000b
	add al,30h
	mov bx,0
	pop bx
	ret

display:
	push ax
	push bx
	mov bp,sp
	mov cx,4
	mov ah,0eh
ll:
	mov al,ss:[bp]
	int 10h
	inc bp
	loop ll
	pop ax
	pop bx
	ret

code ends

end start
