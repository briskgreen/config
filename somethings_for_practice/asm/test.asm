section .data
	format db "%d",0xa,0

section .text
global main
main:
	extern add_sum
	call add_sum
	extern printf
	push dword [eax]
	push dword format
	call printf

	add esp,byte 8
	ret
