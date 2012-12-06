assume cs:code
one segment
DB 00H,00H,00H,00H,00H,00H,08H,00H,38H,00H,18H,00H,18H,00H,18H,00H,18H,00H,18H,00H,18H,00H,18H,00H,18H,00H,3EH,00H,00H,00H,00H,00H
one ends
two segment
DB 00H,00H,00H,00H,00H,00H,3CH,00H,66H,00H,62H,00H,62H,00H,06H,00H,04H,00H,08H,00H,10H,00H,22H,00H,7EH,00H,7EH,00H,00H,00H,00H,00H
two ends
three segment
DB 00H,00H,00H,00H,00H,00H,3CH,00H,66H,00H,66H,00H,06H,00H,1CH,00H,1CH,00H,06H,00H,02H,00H,62H,00H,66H,00H,3CH,00H,00H,00H,00H,00H
three ends
four segment
DB 00H,00H,00H,00H,00H,00H,04H,00H,0CH,00H,0CH,00H,14H,00H,24H,00H,24H,00H,44H,00H,7FH,00H,04H,00H,04H,00H,1FH,00H,00H,00H,00H,00H
four ends
five segment
DB 00H,00H,00H,00H,00H,00H,3EH,00H,20H,00H,20H,00H,68H,00H,7CH,00H,66H,00H,02H,00H,03H,00H,62H,00H,66H,00H,3CH,00H,00H,00H,00H,00H
five ends
six segment
DB 00H,00H,00H,00H,00H,00H,1CH,00H,26H,00H,60H,00H,60H,00H,7EH,00H,62H,00H,63H,00H,63H,00H,63H,00H,22H,00H,1CH,00H,00H,00H,00H,00H
six ends
seven segment
DB 00H,00H,00H,00H,00H,00H,7FH,00H,62H,00H,46H,00H,04H,00H,0CH,00H,08H,00H,08H,00H,18H,00H,18H,00H,18H,00H,18H,00H,00H,00H,00H,00H
seven ends
eite segment
DB 00H,00H,00H,00H,00H,00H,3CH,00H,62H,00H,62H,00H,62H,00H,3CH,00H,3CH,00H,66H,00H,42H,00H,43H,00H,62H,00H,3CH,00H,00H,00H,00H,00H
eite ends
nite segment
DB 00H,00H,00H,00H,00H,00H,3CH,00H,66H,00H,62H,00H,43H,00H,63H,00H,67H,00H,3BH,00H,02H,00H,26H,00H,64H,00H,38H,00H,00H,00H,00H,00H
nite ends
zero segment
DB 00H,00H,00H,00H,00H,00H,1CH,00H,26H,00H,62H,00H,63H,00H,63H,00H,63H,00H,63H,00H,63H,00H,62H,00H,26H,00H,1CH,00H,00H,00H,00H,00H
zero ends
line segment
DB 00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,18H,00H,18H,00H,00H,00H,00H,00H,00H,00H,00H,00H,18H,00H,18H,00H,00H,00H,00H,00H
line ends
empty segment
DB 00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H,00H
empty ends
code segment
start:
mov ax,0b800H
mov es,ax
mov al,4
out 70H,al
in al,71H
mov ah,al
mov cl,4
shr al,cl
and ah,00001111B
mov bp,16*2+160*5
call number
mov al,ah
mov bp,24*2+160*5
call number
mov dx,line
mov bp,32*2+160*5
call print 
mov al,2
out 70H,al
in al,71H
mov ah,al
mov cl,4
shr al,cl
and ah,00001111B
mov bp,40*2+160*5
call number
mov al,ah
mov bp,48*2+160*5
call number
mov dx,line
mov bp,56*2+160*5
call print 
mov al,0
out 70H,al
in al,71H
mov ah,al
mov cl,4
shr al,cl
and ah,00001111B
mov bp,64*2+160*5
call number
mov al,ah
mov bp,72*2+160*5
call number 
call yanshi 
jmp start
mov ax,4c00H
int 21h
;**********************************************************************
;数字输出子程序，al为参数，为待输出一位十进制数
number:
mov dx,empty
call print 
cmp al,0
ja num1
mov dx,zero
call print
jmp over
num1:
cmp al,1
ja num2
mov dx,one
call print
jmp over
num2:
cmp al,2
ja num3
mov dx,two
call print
jmp over
num3:
cmp al,3
ja num4
mov dx,three
call print
jmp over
num4:
cmp al,4
ja num5
mov dx,four
call print
jmp over
num5:
cmp al,5
ja num6
mov dx,five
call print
jmp over
num6:
cmp al,6
ja num7
mov dx,six
call print
jmp over
num7:
cmp al,7
ja num8
mov dx,seven
call print
jmp over
num8:
cmp al,8
ja num9
mov dx,eite
call print
jmp over
num9:
cmp al,9
ja over
mov dx,nite
call print
jmp over
over :
ret ;*****************************************************************************
print: ;字模输出子程序，参数dx为段地址，参数bp为第一行末地址
push ax
push bx
push cx
push dx
push bp

mov bx,0
mov cx,16
mov ds,dx
s0:

mov ah,ds:[bx]
mov dh,ah
push cx
mov cx,8
s:
and dh,00000001B
cmp dh,0
je s1 
mov dl,01H
mov dh,00001100b
mov es:[bp],dx
jmp s2
s1:
mov dl,0
mov es:[bp],dx
s2:
sub bp,2
shr ah,1
mov dh,ah
loop s
pop cx
add bx,2
add bp,160+8*2
loop s0
pop bp
pop dx
pop cx
pop bx
pop ax
ret
;********************************************************************************
;延时子程序
Delay Proc Near
push dx
push cx
xor ax,ax
int 1ah
mov cs:Times,dx
mov cs:Times[2],cx
Read_Time: xor ax,ax
int 1ah
sub dx,cs:Times
sbb cx,cs:Times[2]
cmp dx,Didas
jb Read_Time
pop cx
pop dx
ret
Times dw 0,0
Delay EndP
Didas equ 9
yanshi: call Delay
ret 
code ends
end start 
