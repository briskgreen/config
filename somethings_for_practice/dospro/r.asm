assume cs:code,ss:stack

stack segment

	dw 200 dup (0)

stack ends

code segment

start:
	mov cx,100
	mov ax,stack
	mov ss,ax
	mov sp,400
	mov ax,1
	mov bl,1
	mov bh,0
	call re

	mov ax,4c00h
	int 21h

re:
	add ax,bx
	cmp bx,cx
	je return
	inc bl
	call re

return:
	ret

code ends

end start
