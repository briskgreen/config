assume cs:code,ds:data,ss:stack

stack segment

	dw 2 dup (0)

stack ends

data segment

	db "Beginner's All-purpose Symbolica Instruction Code.",0

data ends

code segment

start:
	mov ax,stack
	mov ss,ax
	mov sp,4
	mov ax,data
	mov ds,ax
	mov si,0
	call change_letter

	mov ax,4c00h
	int 21h

change_letter:
	mov cl,ds:[si]
	mov ch,0
	jcxz return
	cmp cl,'a'
	jna change
	and cl,11011111b
	mov ds:[si],cl
change:
	inc si
	loop change_letter
return:
	ret

code ends

end start
