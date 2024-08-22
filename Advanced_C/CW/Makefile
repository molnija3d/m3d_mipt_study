all: prg

prg: find_square.o
	gcc -o find_square find_square.o -ggdb3

find_square.o: find_square.c
	gcc -c -o find_square.o find_square.c -ggdb3

clean: 
	rm find_square
	rm *.o   
