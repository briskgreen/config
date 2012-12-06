assume cs:code

code segment

start:
	mov ah,02
	mov dl,'s'
	int 21h

	mov ah,02
	mov dl,'b'
	int 21h
	
	mov ax,4c00h
	int 21h

code ends

end start
