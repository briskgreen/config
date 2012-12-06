section .data
	hello db "Hello World!",0xa,0
	len db 0

section .text
global _start
_start:
	mov edx,len-hello
	mov ecx,hello
	mov ebx,1
	mov eax,4
	int 0x80

	mov ebx,0
	mov eax,1
	int 0x80
