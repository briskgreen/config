assume cs:code

code segment

start:
	mov ax,0
	mov es,ax
	mov di,200h
	mov ax,cs
	mov ds,ax
	mov si,offset sisplay
	mov cx,offset sisplay_end-offset sisplay
	cld
	rep movsb

	mov ax,0
	mov es,ax
	mov word ptr es:[7ch*4],200h
	mov word ptr es:[7ch*4+2],0

	mov ax,4c00h
	int 21h

sisplay:
	mov ah,2
	mov bh,0
	int 10h
	mov ah,9
	mov bl,cl
	dec dl
l:
	mov cl,ds:[si]
	jcxz return
	inc dl
	mov al,cl
	inc si
	mov cx,1
	int 10h
	jmp short l
return:
	iret
sisplay_end:
	nop

code ends

end start
