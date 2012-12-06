assume cs:code,ss:stack,ds:data

data segment

	db 'Hello World!',0

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
	mov si,0
	call display

	mov ax,4c00h
	int 21h

display:
	push si
	mov ah,0eh
	mov dl,0
l:
	mov al,ds:[si]
	cmp al,0
	je return
	int 10h
	inc si
	jmp short l
return:
	pop si
	ret

code ends

end start
