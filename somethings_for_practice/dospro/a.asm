assume cs:code,ds:data,ss:stack

data segment

	db 'word',0
	db 'unix',0
	db 'wind',0
	db 'good',0

data ends

stack segment

	dw 2 dup (0)

stack ends

code segment

start:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,4
	mov cx,4
	mov bx,0

l:
	push cx
	mov si,bx
	call change
	pop cx
	add bx,5
	loop l

	mov ax,4c00h
	int 21h

change:
	mov cl,ds:[si]
	mov ch,0
	jcxz return
	and byte ptr ds:[si],11011111b
	inc si
	jmp short change
return:
	ret

code ends

end start
