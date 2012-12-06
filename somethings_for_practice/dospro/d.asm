assume cs:code

code segment

start:
	mov ax,10
	shl ax,1
	mov bx,ax
	mov cl,4
	shl bx,cl
	add ax,bx

	mov ax,4c00h
	int 21h

code ends

end start
