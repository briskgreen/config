assume cs:code,ds:data,ss:stack

stack segment

	dw 8 dup (0)

stack ends

data segment

	db 'Wellcome to masm!',0

data ends

code segment

start:
	mov dh,8
	mov dl,3
	mov cl,2
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,16
	call show_str

	mov ax,4c00h
	int 21h

show_str:
	mov di,0
	push cx
	mov al,dl
	mov ah,0
	mov cx,ax
	dec cx
	mov dl,0
x:
	add dl,2
	loop x
	pop cx
	mov al,dl
	mov ah,0
	mov si,ax
	push cx
	mov al,dh
	mov ah,0
	mov cx,ax
	dec cx
	mov dh,0
y:
	add dh,0ah
	loop y
	pop cx
	mov ah,0b8h
	mov al,dh
	mov es,ax
print:
	push cx
	mov cl,ds:[di]
	mov ch,0
	jcxz return
	pop cx
	mov al,ds:[di]
	mov es:[si],al
	mov es:[si].1,cl
	add si,2
	inc di
	jmp short print
return:
	pop cx
	ret

code ends

end start
