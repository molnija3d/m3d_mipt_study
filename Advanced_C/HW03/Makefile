all: snake	
	./snake.exe
snake: snake.o 
	gcc -o snake.exe snake.o -l:libncursesw.dll.a

snake.o: snake.c
	gcc -c -o snake.o snake.c -I c:\msys64\ucrt64\include\ncurses\

clean: 
	del *.exe 
	del *.o   