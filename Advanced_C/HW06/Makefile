all: snake	
	./snake
snake: snake.o 
	gcc -o snake snake.o -lncurses -pg

snake.o: snake.c
	gcc -c -o snake.o snake.c

clean: 
	rm ./snake 
	rm *.o   
