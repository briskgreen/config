test:test.o my.o
	gcc -o test test.o my.o
test.o:test.asm
	nasm -f elf test.asm
my.o:my.c
	gcc -c my.c
clean:
	rm test test.o my.o
