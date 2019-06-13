all:test

test:foo.o test.o
	ld --dynamic-linker /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 -lc -m elf_x86_64 -s -o test foo.o test.o

foo.o:foo.c
	gcc -c foo.c -o foo.o

test.o:test.asm
	nasm -f elf64 -o test.o test.asm


